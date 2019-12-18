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
typedef  TYPE_1__* grub_symbol_t ;
struct TYPE_3__ {void* addr; int /*<<< orphan*/  name; struct TYPE_3__* next; } ;

/* Variables and functions */
 scalar_t__ grub_strcmp (int /*<<< orphan*/ ,char const*) ; 
 size_t grub_symbol_hash (char const*) ; 
 TYPE_1__** grub_symtab ; 

__attribute__((used)) static void *
grub_dl_resolve_symbol (const char *name)
{
  grub_symbol_t sym;

  for (sym = grub_symtab[grub_symbol_hash (name)]; sym; sym = sym->next)
    if (grub_strcmp (sym->name, name) == 0)
      return sym->addr;

  return 0;
}