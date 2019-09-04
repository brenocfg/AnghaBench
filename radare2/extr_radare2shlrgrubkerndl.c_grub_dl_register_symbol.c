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
typedef  TYPE_1__* grub_symbol_t ;
typedef  int /*<<< orphan*/  grub_err_t ;
typedef  scalar_t__ grub_dl_t ;
struct TYPE_4__ {char const* name; struct TYPE_4__* next; scalar_t__ mod; void* addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_NONE ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_free (TYPE_1__*) ; 
 scalar_t__ grub_malloc (int) ; 
 char const* grub_strdup (char const*) ; 
 unsigned int grub_symbol_hash (char const*) ; 
 TYPE_1__** grub_symtab ; 

grub_err_t
grub_dl_register_symbol (const char *name, void *addr, grub_dl_t mod)
{
  grub_symbol_t sym;
  unsigned k;

  sym = (grub_symbol_t) grub_malloc (sizeof (*sym));
  if (! sym)
    return grub_errno;

  if (mod)
    {
      sym->name = grub_strdup (name);
      if (! sym->name)
	{
	  grub_free (sym);
	  return grub_errno;
	}
    }
  else
    sym->name = name;

  sym->addr = addr;
  sym->mod = mod;

  k = grub_symbol_hash (name);
  sym->next = grub_symtab[k];
  grub_symtab[k] = sym;

  return GRUB_ERR_NONE;
}