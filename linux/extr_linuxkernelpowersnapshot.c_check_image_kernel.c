#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  machine; int /*<<< orphan*/  version; int /*<<< orphan*/  release; int /*<<< orphan*/  sysname; } ;
struct swsusp_info {scalar_t__ version_code; TYPE_1__ uts; } ;
struct TYPE_4__ {int /*<<< orphan*/  machine; int /*<<< orphan*/  version; int /*<<< orphan*/  release; int /*<<< orphan*/  sysname; } ;

/* Variables and functions */
 scalar_t__ LINUX_VERSION_CODE ; 
 TYPE_2__* init_utsname () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *check_image_kernel(struct swsusp_info *info)
{
	if (info->version_code != LINUX_VERSION_CODE)
		return "kernel version";
	if (strcmp(info->uts.sysname,init_utsname()->sysname))
		return "system type";
	if (strcmp(info->uts.release,init_utsname()->release))
		return "kernel release";
	if (strcmp(info->uts.version,init_utsname()->version))
		return "version";
	if (strcmp(info->uts.machine,init_utsname()->machine))
		return "machine";
	return NULL;
}