#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct brcmf_if {TYPE_1__* drvr; } ;
typedef  enum brcmf_feat_id { ____Placeholder_brcmf_feat_id } brcmf_feat_id ;
typedef  int /*<<< orphan*/  caps ;
struct TYPE_5__ {int feature; int /*<<< orphan*/  fwcap_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  feat_flags; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  INFO ; 
 int MAX_CAPS_BUFFER_SIZE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  brcmf_err (char*,int) ; 
 char** brcmf_feat_names ; 
 int brcmf_fil_iovar_data_get (struct brcmf_if*,char*,char*,int) ; 
 TYPE_2__* brcmf_fwcap_map ; 
 scalar_t__ strnstr (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void brcmf_feat_firmware_capabilities(struct brcmf_if *ifp)
{
	char caps[MAX_CAPS_BUFFER_SIZE];
	enum brcmf_feat_id id;
	int i, err;

	err = brcmf_fil_iovar_data_get(ifp, "cap", caps, sizeof(caps));
	if (err) {
		brcmf_err("could not get firmware cap (%d)\n", err);
		return;
	}

	brcmf_dbg(INFO, "[ %s]\n", caps);

	for (i = 0; i < ARRAY_SIZE(brcmf_fwcap_map); i++) {
		if (strnstr(caps, brcmf_fwcap_map[i].fwcap_id, sizeof(caps))) {
			id = brcmf_fwcap_map[i].feature;
			brcmf_dbg(INFO, "enabling feature: %s\n",
				  brcmf_feat_names[id]);
			ifp->drvr->feat_flags |= BIT(id);
		}
	}
}