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
 int /*<<< orphan*/  ADD (char*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  DEF_FIELD (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ VIRTIO_DEV_ANY_ID ; 
 int /*<<< orphan*/  add_wildcard (char*) ; 
 scalar_t__ device ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ vendor ; 
 int /*<<< orphan*/  virtio_device_id ; 

__attribute__((used)) static int do_virtio_entry(const char *filename, void *symval,
			   char *alias)
{
	DEF_FIELD(symval, virtio_device_id, device);
	DEF_FIELD(symval, virtio_device_id, vendor);

	strcpy(alias, "virtio:");
	ADD(alias, "d", device != VIRTIO_DEV_ANY_ID, device);
	ADD(alias, "v", vendor != VIRTIO_DEV_ANY_ID, vendor);

	add_wildcard(alias);
	return 1;
}