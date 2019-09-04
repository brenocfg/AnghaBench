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
struct us_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dissociate_dev (struct us_data*) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  us_to_host (struct us_data*) ; 
 int /*<<< orphan*/  usb_stor_release_resources (struct us_data*) ; 

__attribute__((used)) static void release_everything(struct us_data *us)
{
	usb_stor_release_resources(us);
	dissociate_dev(us);

	/*
	 * Drop our reference to the host; the SCSI core will free it
	 * (and "us" along with it) when the refcount becomes 0.
	 */
	scsi_host_put(us_to_host(us));
}