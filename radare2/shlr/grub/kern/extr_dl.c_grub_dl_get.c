#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* grub_dl_t ;
typedef  TYPE_2__* grub_dl_list_t ;
struct TYPE_6__ {TYPE_1__* mod; struct TYPE_6__* next; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_2__* grub_dl_head ; 
 scalar_t__ grub_strcmp (char const*,int /*<<< orphan*/ ) ; 

grub_dl_t
grub_dl_get (const char *name)
{
  grub_dl_list_t l;

  for (l = grub_dl_head; l; l = l->next)
    if (grub_strcmp (name, l->mod->name) == 0)
      return l->mod;

  return 0;
}