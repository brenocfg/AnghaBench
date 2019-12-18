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
struct TYPE_2__ {int flags; } ;
struct xfrm_state {TYPE_1__ props; struct crypto_aead* data; } ;
struct scatterlist {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {scalar_t__ src; scalar_t__ dst; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int XFRM_STATE_ESN ; 
 int /*<<< orphan*/ * esp_tmp_iv (struct crypto_aead*,void*,int) ; 
 struct aead_request* esp_tmp_req (struct crypto_aead*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

__attribute__((used)) static void esp_ssg_unref(struct xfrm_state *x, void *tmp)
{
	struct crypto_aead *aead = x->data;
	int seqhilen = 0;
	u8 *iv;
	struct aead_request *req;
	struct scatterlist *sg;

	if (x->props.flags & XFRM_STATE_ESN)
		seqhilen += sizeof(__be32);

	iv = esp_tmp_iv(aead, tmp, seqhilen);
	req = esp_tmp_req(aead, iv);

	/* Unref skb_frag_pages in the src scatterlist if necessary.
	 * Skip the first sg which comes from skb->data.
	 */
	if (req->src != req->dst)
		for (sg = sg_next(req->src); sg; sg = sg_next(sg))
			put_page(sg_page(sg));
}