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
struct brcmf_pno_config_le {scalar_t__ flags; scalar_t__ reporttype; } ;
struct brcmf_if {int dummy; } ;

/* Variables and functions */
 int brcmf_fil_iovar_data_set (struct brcmf_if*,char*,struct brcmf_pno_config_le*,int) ; 

__attribute__((used)) static int brcmf_pno_channel_config(struct brcmf_if *ifp,
				    struct brcmf_pno_config_le *cfg)
{
	cfg->reporttype = 0;
	cfg->flags = 0;

	return brcmf_fil_iovar_data_set(ifp, "pfn_cfg", cfg, sizeof(*cfg));
}