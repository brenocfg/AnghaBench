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
typedef  void* u8 ;
struct nfc_llcp_sdp_tlv {int /*<<< orphan*/  node; void* sap; void* tid; int /*<<< orphan*/ * tlv; int /*<<< orphan*/  tlv_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LLCP_TLV_SDRES ; 
 int /*<<< orphan*/  kfree (struct nfc_llcp_sdp_tlv*) ; 
 struct nfc_llcp_sdp_tlv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfc_llcp_build_tlv (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 

struct nfc_llcp_sdp_tlv *nfc_llcp_build_sdres_tlv(u8 tid, u8 sap)
{
	struct nfc_llcp_sdp_tlv *sdres;
	u8 value[2];

	sdres = kzalloc(sizeof(struct nfc_llcp_sdp_tlv), GFP_KERNEL);
	if (sdres == NULL)
		return NULL;

	value[0] = tid;
	value[1] = sap;

	sdres->tlv = nfc_llcp_build_tlv(LLCP_TLV_SDRES, value, 2,
					&sdres->tlv_len);
	if (sdres->tlv == NULL) {
		kfree(sdres);
		return NULL;
	}

	sdres->tid = tid;
	sdres->sap = sap;

	INIT_HLIST_NODE(&sdres->node);

	return sdres;
}