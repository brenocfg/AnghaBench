#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  grub_err_t ;
typedef  TYPE_1__* grub_device_t ;
struct TYPE_4__ {scalar_t__ disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  grub_disk_close (scalar_t__) ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_free (TYPE_1__*) ; 

grub_err_t
grub_device_close (grub_device_t device)
{
  if (device->disk)
    grub_disk_close (device->disk);

  grub_free (device);

  return grub_errno;
}