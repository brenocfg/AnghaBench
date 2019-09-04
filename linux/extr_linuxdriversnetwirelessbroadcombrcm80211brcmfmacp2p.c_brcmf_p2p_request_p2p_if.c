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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct brcmf_p2p_info {int dummy; } ;
struct brcmf_if {int dummy; } ;
struct brcmf_fil_p2p_if_le {void* chspec; void* type; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  if_request ;
typedef  enum brcmf_fil_p2p_if_types { ____Placeholder_brcmf_fil_p2p_if_types } brcmf_fil_p2p_if_types ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int brcmf_fil_iovar_data_set (struct brcmf_if*,char*,struct brcmf_fil_p2p_if_le*,int) ; 
 int /*<<< orphan*/  brcmf_p2p_get_current_chanspec (struct brcmf_p2p_info*,int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_p2p_request_p2p_if(struct brcmf_p2p_info *p2p,
				    struct brcmf_if *ifp, u8 ea[ETH_ALEN],
				    enum brcmf_fil_p2p_if_types iftype)
{
	struct brcmf_fil_p2p_if_le if_request;
	int err;
	u16 chanspec;

	/* we need a default channel */
	brcmf_p2p_get_current_chanspec(p2p, &chanspec);

	/* fill the firmware request */
	memcpy(if_request.addr, ea, ETH_ALEN);
	if_request.type = cpu_to_le16((u16)iftype);
	if_request.chspec = cpu_to_le16(chanspec);

	err = brcmf_fil_iovar_data_set(ifp, "p2p_ifadd", &if_request,
				       sizeof(if_request));

	return err;
}