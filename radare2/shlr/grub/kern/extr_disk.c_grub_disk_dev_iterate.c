#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* grub_disk_dev_t ;
struct TYPE_3__ {scalar_t__ (* iterate ) (int (*) (char const*,void*),void*) ;struct TYPE_3__* next; } ;

/* Variables and functions */
 TYPE_1__* grub_disk_dev_list ; 
 scalar_t__ stub1 (int (*) (char const*,void*),void*) ; 

int
grub_disk_dev_iterate (int (*hook) (const char *name, void *closure),
		       void *closure)
{
  grub_disk_dev_t p;

  for (p = grub_disk_dev_list; p; p = p->next)
    if (p->iterate && (p->iterate) (hook, closure))
      return 1;

  return 0;
}