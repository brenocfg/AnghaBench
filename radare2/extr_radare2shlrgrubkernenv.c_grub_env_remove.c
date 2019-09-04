#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct grub_env_var {TYPE_1__** prevp; TYPE_1__* next; } ;
struct TYPE_2__ {struct TYPE_2__** prevp; } ;

/* Variables and functions */

__attribute__((used)) static void
grub_env_remove (struct grub_env_var *var)
{
  /* Remove the entry from the variable table.  */
  *var->prevp = var->next;
  if (var->next)
    var->next->prevp = var->prevp;
}