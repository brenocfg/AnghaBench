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

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int EINVAL ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/ ** wks ; 

__attribute__((used)) static int nfc_llcp_wks_sap(char *service_name, size_t service_name_len)
{
	int sap, num_wks;

	pr_debug("%s\n", service_name);

	if (service_name == NULL)
		return -EINVAL;

	num_wks = ARRAY_SIZE(wks);

	for (sap = 0; sap < num_wks; sap++) {
		if (wks[sap] == NULL)
			continue;

		if (strncmp(wks[sap], service_name, service_name_len) == 0)
			return sap;
	}

	return -EINVAL;
}