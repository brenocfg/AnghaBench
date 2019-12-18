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
struct ceph_osd_client {int /*<<< orphan*/  lock; scalar_t__ abort_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void ceph_osdc_clear_abort_err(struct ceph_osd_client *osdc)
{
	down_write(&osdc->lock);
	osdc->abort_err = 0;
	up_write(&osdc->lock);
}