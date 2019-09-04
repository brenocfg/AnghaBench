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
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int SDEBUG_INFO_LEN ; 
 int /*<<< orphan*/  SDEBUG_VERSION ; 
 int /*<<< orphan*/  my_name ; 
 int scnprintf (char const*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  sdebug_dev_size_mb ; 
 char const* sdebug_info ; 
 int /*<<< orphan*/  sdebug_opts ; 
 scalar_t__ sdebug_statistics ; 
 int /*<<< orphan*/  sdebug_version_date ; 
 int /*<<< orphan*/  submit_queues ; 

__attribute__((used)) static const char *scsi_debug_info(struct Scsi_Host *shp)
{
	int k;

	k = scnprintf(sdebug_info, SDEBUG_INFO_LEN, "%s: version %s [%s]\n",
		      my_name, SDEBUG_VERSION, sdebug_version_date);
	if (k >= (SDEBUG_INFO_LEN - 1))
		return sdebug_info;
	scnprintf(sdebug_info + k, SDEBUG_INFO_LEN - k,
		  "  dev_size_mb=%d, opts=0x%x, submit_queues=%d, %s=%d",
		  sdebug_dev_size_mb, sdebug_opts, submit_queues,
		  "statistics", (int)sdebug_statistics);
	return sdebug_info;
}