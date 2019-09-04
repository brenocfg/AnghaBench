#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hif_scatter_req {int virt_scat; struct bus_request* busrequest; struct hif_scatter_req* virt_dma_buf; struct hif_scatter_req* sgentries; } ;
typedef  struct hif_scatter_req u8 ;
struct scatterlist {int dummy; } ;
struct hif_scatter_item {int dummy; } ;
struct bus_request {struct hif_scatter_req* scat_req; } ;
struct ath6kl_sdio {int /*<<< orphan*/  ar; } ;

/* Variables and functions */
 int ATH6KL_MAX_TRANSFER_SIZE_PER_SCATTER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ L1_CACHE_ALIGN (unsigned long) ; 
 int L1_CACHE_BYTES ; 
 struct bus_request* ath6kl_sdio_alloc_busreq (struct ath6kl_sdio*) ; 
 int /*<<< orphan*/  hif_scatter_req_add (int /*<<< orphan*/ ,struct hif_scatter_req*) ; 
 int /*<<< orphan*/  kfree (struct hif_scatter_req*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_sdio_alloc_prep_scat_req(struct ath6kl_sdio *ar_sdio,
					   int n_scat_entry, int n_scat_req,
					   bool virt_scat)
{
	struct hif_scatter_req *s_req;
	struct bus_request *bus_req;
	int i, scat_req_sz, scat_list_sz, size;
	u8 *virt_buf;

	scat_list_sz = n_scat_entry * sizeof(struct hif_scatter_item);
	scat_req_sz = sizeof(*s_req) + scat_list_sz;

	if (!virt_scat)
		size = sizeof(struct scatterlist) * n_scat_entry;
	else
		size =  2 * L1_CACHE_BYTES +
			ATH6KL_MAX_TRANSFER_SIZE_PER_SCATTER;

	for (i = 0; i < n_scat_req; i++) {
		/* allocate the scatter request */
		s_req = kzalloc(scat_req_sz, GFP_KERNEL);
		if (!s_req)
			return -ENOMEM;

		if (virt_scat) {
			virt_buf = kzalloc(size, GFP_KERNEL);
			if (!virt_buf) {
				kfree(s_req);
				return -ENOMEM;
			}

			s_req->virt_dma_buf =
				(u8 *)L1_CACHE_ALIGN((unsigned long)virt_buf);
		} else {
			/* allocate sglist */
			s_req->sgentries = kzalloc(size, GFP_KERNEL);

			if (!s_req->sgentries) {
				kfree(s_req);
				return -ENOMEM;
			}
		}

		/* allocate a bus request for this scatter request */
		bus_req = ath6kl_sdio_alloc_busreq(ar_sdio);
		if (!bus_req) {
			kfree(s_req->sgentries);
			kfree(s_req->virt_dma_buf);
			kfree(s_req);
			return -ENOMEM;
		}

		/* assign the scatter request to this bus request */
		bus_req->scat_req = s_req;
		s_req->busrequest = bus_req;

		s_req->virt_scat = virt_scat;

		/* add it to the scatter pool */
		hif_scatter_req_add(ar_sdio->ar, s_req);
	}

	return 0;
}