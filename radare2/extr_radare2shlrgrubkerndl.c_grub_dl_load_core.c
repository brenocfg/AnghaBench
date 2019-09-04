#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct grub_obj_header {scalar_t__ magic; scalar_t__ version; int mod_deps; } ;
typedef  scalar_t__ grub_size_t ;
typedef  TYPE_1__* grub_dl_t ;
struct TYPE_12__ {int ref_count; struct TYPE_12__* init; struct TYPE_12__* name; scalar_t__ fini; scalar_t__ segment; scalar_t__ dep; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_OS ; 
 scalar_t__ GRUB_OBJ_HEADER_MAGIC ; 
 scalar_t__ GRUB_OBJ_HEADER_VERSION ; 
 scalar_t__ grub_dl_add (TYPE_1__*) ; 
 int /*<<< orphan*/  grub_dl_call_init (TYPE_1__*) ; 
 int /*<<< orphan*/  grub_dl_flush_cache (TYPE_1__*) ; 
 scalar_t__ grub_dl_load_segments (TYPE_1__*,struct grub_obj_header*) ; 
 scalar_t__ grub_dl_resolve_dependencies (TYPE_1__*,char*) ; 
 scalar_t__ grub_dl_resolve_symbols (TYPE_1__*,struct grub_obj_header*) ; 
 int /*<<< orphan*/  grub_dl_unload (TYPE_1__*) ; 
 int /*<<< orphan*/  grub_dprintf (char*,char*,TYPE_1__*,...) ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ grub_malloc (int) ; 
 TYPE_1__* grub_strdup (char*) ; 

grub_dl_t
grub_dl_load_core (void *addr, grub_size_t size)
{
  struct grub_obj_header *e;
  grub_dl_t mod;
  char *name;

  grub_dprintf ("modules", "module at %p, size 0x%lx\n", addr,
		(unsigned long) size);

  e = addr;
  if ((e->magic != GRUB_OBJ_HEADER_MAGIC) ||
      (e->version != GRUB_OBJ_HEADER_VERSION))
    {
      grub_error (GRUB_ERR_BAD_OS, "invalid object file");
      return 0;
    }

  mod = (grub_dl_t) grub_malloc (sizeof (*mod));
  if (! mod)
    return 0;

  name = (char *) addr + e->mod_deps;

  mod->name = grub_strdup (name);
  mod->ref_count = 1;
  mod->dep = 0;
  mod->segment = 0;
  mod->init = 0;
  mod->fini = 0;

  grub_dprintf ("modules", "relocating to %p\n", mod);
  if (grub_dl_resolve_dependencies (mod, name)
      || grub_dl_load_segments (mod, e)
      || grub_dl_resolve_symbols (mod, e))
    {
      mod->fini = 0;
      grub_dl_unload (mod);
      return 0;
    }

  grub_dl_flush_cache (mod);

  grub_dprintf ("modules", "module name: %s\n", mod->name);
  grub_dprintf ("modules", "init function: %p\n", mod->init);
  grub_dl_call_init (mod);

  if (grub_dl_add (mod))
    {
      grub_dl_unload (mod);
      return 0;
    }

  return mod;
}