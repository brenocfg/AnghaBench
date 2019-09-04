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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEGMENT_SHARED ; 
 int /*<<< orphan*/  mon_dcss_end ; 
 int /*<<< orphan*/  mon_dcss_name ; 
 int /*<<< orphan*/  mon_dcss_start ; 
 int monreader_thaw (struct device*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int segment_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  segment_unload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  segment_warning (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int monreader_restore(struct device *dev)
{
	int rc;

	segment_unload(mon_dcss_name);
	rc = segment_load(mon_dcss_name, SEGMENT_SHARED,
			  &mon_dcss_start, &mon_dcss_end);
	if (rc < 0) {
		segment_warning(rc, mon_dcss_name);
		panic("fatal monreader resume error: no monitor dcss\n");
	}
	return monreader_thaw(dev);
}