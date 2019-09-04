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
struct hpsa_scsi_dev_t {int /*<<< orphan*/  physical_device; } ;

/* Variables and functions */

__attribute__((used)) static inline bool is_logical_device(struct hpsa_scsi_dev_t *device)
{
	return !device->physical_device;
}