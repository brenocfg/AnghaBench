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
struct device_driver {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ map_size ; 
 int /*<<< orphan*/  map_storep ; 
 size_t scnprintf (char*,scalar_t__,char*,int,...) ; 
 int /*<<< orphan*/  scsi_debug_lbp () ; 
 int /*<<< orphan*/  sdebug_store_sectors ; 

__attribute__((used)) static ssize_t map_show(struct device_driver *ddp, char *buf)
{
	ssize_t count;

	if (!scsi_debug_lbp())
		return scnprintf(buf, PAGE_SIZE, "0-%u\n",
				 sdebug_store_sectors);

	count = scnprintf(buf, PAGE_SIZE - 1, "%*pbl",
			  (int)map_size, map_storep);
	buf[count++] = '\n';
	buf[count] = '\0';

	return count;
}