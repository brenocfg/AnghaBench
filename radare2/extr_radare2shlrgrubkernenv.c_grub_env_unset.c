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
struct grub_env_var {struct grub_env_var* value; struct grub_env_var* name; scalar_t__ write_hook; scalar_t__ read_hook; } ;

/* Variables and functions */
 struct grub_env_var* grub_env_find (char const*) ; 
 int /*<<< orphan*/  grub_env_remove (struct grub_env_var*) ; 
 int /*<<< orphan*/  grub_env_set (char const*,char*) ; 
 int /*<<< orphan*/  grub_free (struct grub_env_var*) ; 

void
grub_env_unset (const char *name)
{
  struct grub_env_var *var;

  var = grub_env_find (name);
  if (! var)
    return;

  if (var->read_hook || var->write_hook)
    {
      grub_env_set (name, "");
      return;
    }

  grub_env_remove (var);

  grub_free (var->name);
  grub_free (var->value);
  grub_free (var);
}