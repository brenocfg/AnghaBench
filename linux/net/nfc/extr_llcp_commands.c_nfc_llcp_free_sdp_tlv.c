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
struct nfc_llcp_sdp_tlv {struct nfc_llcp_sdp_tlv* tlv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfc_llcp_sdp_tlv*) ; 

void nfc_llcp_free_sdp_tlv(struct nfc_llcp_sdp_tlv *sdp)
{
	kfree(sdp->tlv);
	kfree(sdp);
}