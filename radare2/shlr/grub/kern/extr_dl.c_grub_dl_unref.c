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
typedef  TYPE_1__* grub_dl_t ;
typedef  TYPE_2__* grub_dl_dep_t ;
struct TYPE_5__ {TYPE_1__* mod; struct TYPE_5__* next; } ;
struct TYPE_4__ {int ref_count; TYPE_2__* dep; } ;

/* Variables and functions */

int
grub_dl_unref (grub_dl_t mod)
{
  grub_dl_dep_t dep;

  for (dep = mod->dep; dep; dep = dep->next)
    grub_dl_unref (dep->mod);

  return --mod->ref_count;
}