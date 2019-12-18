#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * hundredth; int /*<<< orphan*/ * second; int /*<<< orphan*/ * minute; int /*<<< orphan*/ * hour; int /*<<< orphan*/ * day; int /*<<< orphan*/ * month; int /*<<< orphan*/ * year; } ;
struct TYPE_6__ {TYPE_1__ modified; } ;
struct grub_iso9660_data {TYPE_2__ voldesc; } ;
typedef  int /*<<< orphan*/  grub_err_t ;
typedef  int /*<<< orphan*/  grub_disk_t ;
typedef  TYPE_3__* grub_device_t ;
struct TYPE_7__ {int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_NUMBER ; 
 int /*<<< orphan*/  grub_dl_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_dl_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  grub_free (struct grub_iso9660_data*) ; 
 struct grub_iso9660_data* grub_iso9660_mount (int /*<<< orphan*/ ) ; 
 char* grub_xasprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_mod ; 

__attribute__((used)) static grub_err_t
grub_iso9660_uuid (grub_device_t device, char **uuid)
{
  struct grub_iso9660_data *data;
  grub_disk_t disk = device->disk;

  grub_dl_ref (my_mod);

  data = grub_iso9660_mount (disk);
  if (data)
    {
      if (! data->voldesc.modified.year[0] && ! data->voldesc.modified.year[1]
	  && ! data->voldesc.modified.year[2] && ! data->voldesc.modified.year[3]
	  && ! data->voldesc.modified.month[0] && ! data->voldesc.modified.month[1]
	  && ! data->voldesc.modified.day[0] && ! data->voldesc.modified.day[1]
	  && ! data->voldesc.modified.hour[0] && ! data->voldesc.modified.hour[1]
	  && ! data->voldesc.modified.minute[0] && ! data->voldesc.modified.minute[1]
	  && ! data->voldesc.modified.second[0] && ! data->voldesc.modified.second[1]
	  && ! data->voldesc.modified.hundredth[0] && ! data->voldesc.modified.hundredth[1])
	{
	  grub_error (GRUB_ERR_BAD_NUMBER, "no creation date in filesystem to generate UUID");
	  *uuid = NULL;
	}
      else
	{
	  *uuid = grub_xasprintf ("%c%c%c%c-%c%c-%c%c-%c%c-%c%c-%c%c-%c%c",
				 data->voldesc.modified.year[0],
				 data->voldesc.modified.year[1],
				 data->voldesc.modified.year[2],
				 data->voldesc.modified.year[3],
				 data->voldesc.modified.month[0],
				 data->voldesc.modified.month[1],
				 data->voldesc.modified.day[0],
				 data->voldesc.modified.day[1],
				 data->voldesc.modified.hour[0],
				 data->voldesc.modified.hour[1],
				 data->voldesc.modified.minute[0],
				 data->voldesc.modified.minute[1],
				 data->voldesc.modified.second[0],
				 data->voldesc.modified.second[1],
				 data->voldesc.modified.hundredth[0],
				 data->voldesc.modified.hundredth[1]);
	}
    }
  else
    *uuid = NULL;

	grub_dl_unref (my_mod);

  grub_free (data);

  return grub_errno;
}