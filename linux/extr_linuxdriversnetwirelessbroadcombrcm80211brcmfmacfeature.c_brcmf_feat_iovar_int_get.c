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
typedef  int /*<<< orphan*/  u32 ;
struct brcmf_if {int fwil_fwerr; TYPE_1__* drvr; } ;
typedef  enum brcmf_feat_id { ____Placeholder_brcmf_feat_id } brcmf_feat_id ;
struct TYPE_2__ {int /*<<< orphan*/  feat_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * brcmf_feat_names ; 
 int brcmf_fil_iovar_int_get (struct brcmf_if*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void brcmf_feat_iovar_int_get(struct brcmf_if *ifp,
				     enum brcmf_feat_id id, char *name)
{
	u32 data;
	int err;

	/* we need to know firmware error */
	ifp->fwil_fwerr = true;

	err = brcmf_fil_iovar_int_get(ifp, name, &data);
	if (err == 0) {
		brcmf_dbg(INFO, "enabling feature: %s\n", brcmf_feat_names[id]);
		ifp->drvr->feat_flags |= BIT(id);
	} else {
		brcmf_dbg(TRACE, "%s feature check failed: %d\n",
			  brcmf_feat_names[id], err);
	}

	ifp->fwil_fwerr = false;
}