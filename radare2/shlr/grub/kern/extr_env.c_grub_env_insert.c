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
struct grub_env_var {struct grub_env_var* next; struct grub_env_var** prevp; int /*<<< orphan*/  name; } ;
struct grub_env_context {struct grub_env_var** vars; } ;

/* Variables and functions */
 int grub_env_hashval (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
grub_env_insert (struct grub_env_context *context,
		 struct grub_env_var *var)
{
  int idx = grub_env_hashval (var->name);

  /* Insert the variable into the hashtable.  */
  var->prevp = &context->vars[idx];
  var->next = context->vars[idx];
  if (var->next)
    var->next->prevp = &(var->next);
  context->vars[idx] = var;
}