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
struct riva_par {unsigned char* EDID; } ;
struct pci_dev {int dummy; } ;
struct fb_info {struct riva_par* par; } ;
struct device_node {struct device_node* child; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVTRACE (char*) ; 
 int /*<<< orphan*/  NVTRACE_ENTER () ; 
 int /*<<< orphan*/  NVTRACE_LEAVE () ; 
 unsigned char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* pci_device_to_OF_node (struct pci_dev*) ; 
 scalar_t__ strncmp (unsigned char const*,char*,int) ; 

__attribute__((used)) static int riva_get_EDID_OF(struct fb_info *info, struct pci_dev *pd)
{
	struct riva_par *par = info->par;
	struct device_node *dp;
	const unsigned char *pedid = NULL;
	const unsigned char *disptype = NULL;
	static char *propnames[] = {
		"DFP,EDID", "LCD,EDID", "EDID", "EDID1", "EDID,B", "EDID,A", NULL };
	int i;

	NVTRACE_ENTER();
	dp = pci_device_to_OF_node(pd);
	for (; dp != NULL; dp = dp->child) {
		disptype = of_get_property(dp, "display-type", NULL);
		if (disptype == NULL)
			continue;
		if (strncmp(disptype, "LCD", 3) != 0)
			continue;
		for (i = 0; propnames[i] != NULL; ++i) {
			pedid = of_get_property(dp, propnames[i], NULL);
			if (pedid != NULL) {
				par->EDID = (unsigned char *)pedid;
				NVTRACE("LCD found.\n");
				return 1;
			}
		}
	}
	NVTRACE_LEAVE();
	return 0;
}