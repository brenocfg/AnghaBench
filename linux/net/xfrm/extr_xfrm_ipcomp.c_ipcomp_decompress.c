#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct xfrm_state {struct ipcomp_data* data; } ;
struct sk_buff {int len; int truesize; int data_len; int /*<<< orphan*/ * data; } ;
struct page {int dummy; } ;
struct ipcomp_data {int /*<<< orphan*/  tfms; } ;
struct ip_comp_hdr {int dummy; } ;
struct crypto_comp {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_2__ {scalar_t__ nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IPCOMP_SCRATCH_SIZE ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 int PAGE_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __skb_frag_set_page (int /*<<< orphan*/ *,struct page*) ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,int) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int crypto_comp_decompress (struct crypto_comp*,int /*<<< orphan*/  const*,int const,int /*<<< orphan*/ *,int*) ; 
 int get_cpu () ; 
 int /*<<< orphan*/  ipcomp_scratches ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 void** per_cpu_ptr (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_frag_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_off_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size_set (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static int ipcomp_decompress(struct xfrm_state *x, struct sk_buff *skb)
{
	struct ipcomp_data *ipcd = x->data;
	const int plen = skb->len;
	int dlen = IPCOMP_SCRATCH_SIZE;
	const u8 *start = skb->data;
	const int cpu = get_cpu();
	u8 *scratch = *per_cpu_ptr(ipcomp_scratches, cpu);
	struct crypto_comp *tfm = *per_cpu_ptr(ipcd->tfms, cpu);
	int err = crypto_comp_decompress(tfm, start, plen, scratch, &dlen);
	int len;

	if (err)
		goto out;

	if (dlen < (plen + sizeof(struct ip_comp_hdr))) {
		err = -EINVAL;
		goto out;
	}

	len = dlen - plen;
	if (len > skb_tailroom(skb))
		len = skb_tailroom(skb);

	__skb_put(skb, len);

	len += plen;
	skb_copy_to_linear_data(skb, scratch, len);

	while ((scratch += len, dlen -= len) > 0) {
		skb_frag_t *frag;
		struct page *page;

		err = -EMSGSIZE;
		if (WARN_ON(skb_shinfo(skb)->nr_frags >= MAX_SKB_FRAGS))
			goto out;

		frag = skb_shinfo(skb)->frags + skb_shinfo(skb)->nr_frags;
		page = alloc_page(GFP_ATOMIC);

		err = -ENOMEM;
		if (!page)
			goto out;

		__skb_frag_set_page(frag, page);

		len = PAGE_SIZE;
		if (dlen < len)
			len = dlen;

		skb_frag_off_set(frag, 0);
		skb_frag_size_set(frag, len);
		memcpy(skb_frag_address(frag), scratch, len);

		skb->truesize += len;
		skb->data_len += len;
		skb->len += len;

		skb_shinfo(skb)->nr_frags++;
	}

	err = 0;

out:
	put_cpu();
	return err;
}