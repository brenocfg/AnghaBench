#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct qeth_hdr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_lin; int /*<<< orphan*/  tx_linfail; } ;
struct TYPE_3__ {scalar_t__ performance_stats; } ;
struct qeth_card {TYPE_2__ perf_stats; TYPE_1__ options; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 int E2BIG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,unsigned int const,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int QETH_MAX_BUFFER_ELEMENTS (struct qeth_card*) ; 
 struct qeth_hdr* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_core_header_cache ; 
 int qeth_count_elements (struct sk_buff*,unsigned int) ; 
 int qeth_get_elements_for_range (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,char*,unsigned int) ; 
 int /*<<< orphan*/  skb_is_nonlinear (struct sk_buff*) ; 
 int skb_linearize (struct sk_buff*) ; 
 struct qeth_hdr* skb_push (struct sk_buff*,unsigned int) ; 

int qeth_add_hw_header(struct qeth_card *card, struct sk_buff *skb,
		       struct qeth_hdr **hdr, unsigned int hdr_len,
		       unsigned int proto_len, unsigned int *elements)
{
	const unsigned int max_elements = QETH_MAX_BUFFER_ELEMENTS(card);
	const unsigned int contiguous = proto_len ? proto_len : 1;
	unsigned int __elements;
	addr_t start, end;
	bool push_ok;
	int rc;

check_layout:
	start = (addr_t)skb->data - hdr_len;
	end = (addr_t)skb->data;

	if (qeth_get_elements_for_range(start, end + contiguous) == 1) {
		/* Push HW header into same page as first protocol header. */
		push_ok = true;
		__elements = qeth_count_elements(skb, 0);
	} else if (!proto_len && qeth_get_elements_for_range(start, end) == 1) {
		/* Push HW header into a new page. */
		push_ok = true;
		__elements = 1 + qeth_count_elements(skb, 0);
	} else {
		/* Use header cache, copy protocol headers up. */
		push_ok = false;
		__elements = 1 + qeth_count_elements(skb, proto_len);
	}

	/* Compress skb to fit into one IO buffer: */
	if (__elements > max_elements) {
		if (!skb_is_nonlinear(skb)) {
			/* Drop it, no easy way of shrinking it further. */
			QETH_DBF_MESSAGE(2, "Dropped an oversized skb (Max Elements=%u / Actual=%u / Length=%u).\n",
					 max_elements, __elements, skb->len);
			return -E2BIG;
		}

		rc = skb_linearize(skb);
		if (card->options.performance_stats) {
			if (rc)
				card->perf_stats.tx_linfail++;
			else
				card->perf_stats.tx_lin++;
		}
		if (rc)
			return rc;

		/* Linearization changed the layout, re-evaluate: */
		goto check_layout;
	}

	*elements = __elements;
	/* Add the header: */
	if (push_ok) {
		*hdr = skb_push(skb, hdr_len);
		return hdr_len;
	}
	/* fall back */
	*hdr = kmem_cache_alloc(qeth_core_header_cache, GFP_ATOMIC);
	if (!*hdr)
		return -ENOMEM;
	/* Copy protocol headers behind HW header: */
	skb_copy_from_linear_data(skb, ((char *)*hdr) + hdr_len, proto_len);
	return 0;
}