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
struct grub_iso9660_susp_entry {scalar_t__ sig; } ;
struct grub_iso9660_data {int rockridge; } ;
typedef  int grub_err_t ;

/* Variables and functions */
 scalar_t__ grub_strncmp (char*,char*,int) ; 

__attribute__((used)) static grub_err_t
susp_iterate (struct grub_iso9660_susp_entry *susp_entry,
	      void *closure)
{
  struct grub_iso9660_data *data = closure;
  /* The "ER" entry is used to detect extensions.  The
     `IEEE_P1285' extension means Rock ridge.  */
  if (grub_strncmp ((char *) susp_entry->sig, "ER", 2) == 0)
    {
      data->rockridge = 1;
      return 1;
    }
  return 0;
}