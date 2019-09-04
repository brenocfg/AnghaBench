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
typedef  int u32 ;
struct brcmf_pub {int feat_flags; int /*<<< orphan*/  fwver; } ;
struct brcmf_feat_fwfeat {int feat_flags; int /*<<< orphan*/  fwid; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct brcmf_feat_fwfeat*) ; 
 int BIT (int) ; 
 int BRCMF_FEAT_LAST ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct brcmf_feat_fwfeat* brcmf_feat_fwfeat_map ; 
 int /*<<< orphan*/ * brcmf_feat_names ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmf_feat_firmware_overrides(struct brcmf_pub *drv)
{
	const struct brcmf_feat_fwfeat *e;
	u32 feat_flags = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(brcmf_feat_fwfeat_map); i++) {
		e = &brcmf_feat_fwfeat_map[i];
		if (!strcmp(e->fwid, drv->fwver)) {
			feat_flags = e->feat_flags;
			break;
		}
	}

	if (!feat_flags)
		return;

	for (i = 0; i < BRCMF_FEAT_LAST; i++)
		if (feat_flags & BIT(i))
			brcmf_dbg(INFO, "enabling firmware feature: %s\n",
				  brcmf_feat_names[i]);
	drv->feat_flags |= feat_flags;
}