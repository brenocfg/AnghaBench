#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ volname; } ;
struct grub_iso9660_data {TYPE_1__ voldesc; scalar_t__ joliet; } ;
typedef  int /*<<< orphan*/  grub_uint16_t ;
typedef  int /*<<< orphan*/  grub_err_t ;
typedef  TYPE_2__* grub_device_t ;
struct TYPE_5__ {int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_free (struct grub_iso9660_data*) ; 
 char* grub_iso9660_convert_string (int /*<<< orphan*/ *,int) ; 
 struct grub_iso9660_data* grub_iso9660_mount (int /*<<< orphan*/ ) ; 
 char* grub_strndup (char*,int) ; 

__attribute__((used)) static grub_err_t
grub_iso9660_label (grub_device_t device, char **label)
{
  struct grub_iso9660_data *data;
  data = grub_iso9660_mount (device->disk);

  if (data)
    {
      if (data->joliet)
        *label = grub_iso9660_convert_string
                 ((grub_uint16_t *) &data->voldesc.volname, 16);
      else
        *label = grub_strndup ((char *) data->voldesc.volname, 32);
      grub_free (data);
    }
  else
    *label = 0;

  return grub_errno;
}