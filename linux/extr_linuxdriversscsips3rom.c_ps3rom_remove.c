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
struct ps3_system_bus_device {int /*<<< orphan*/  core; } ;
struct ps3_storage_device {int /*<<< orphan*/  bounce_buf; int /*<<< orphan*/  sbd; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct Scsi_Host* ps3_system_bus_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ps3_system_bus_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ps3stor_teardown (struct ps3_storage_device*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 struct ps3_storage_device* to_ps3_storage_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ps3rom_remove(struct ps3_system_bus_device *_dev)
{
	struct ps3_storage_device *dev = to_ps3_storage_device(&_dev->core);
	struct Scsi_Host *host = ps3_system_bus_get_drvdata(&dev->sbd);

	scsi_remove_host(host);
	ps3stor_teardown(dev);
	scsi_host_put(host);
	ps3_system_bus_set_drvdata(&dev->sbd, NULL);
	kfree(dev->bounce_buf);
	return 0;
}