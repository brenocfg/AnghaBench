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
struct swsusp_info {scalar_t__ num_physpages; } ;

/* Variables and functions */
 int EPERM ; 
 char* check_image_kernel (struct swsusp_info*) ; 
 scalar_t__ get_num_physpages () ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 

__attribute__((used)) static int check_header(struct swsusp_info *info)
{
	char *reason;

	reason = check_image_kernel(info);
	if (!reason && info->num_physpages != get_num_physpages())
		reason = "memory size";
	if (reason) {
		pr_err("Image mismatch: %s\n", reason);
		return -EPERM;
	}
	return 0;
}