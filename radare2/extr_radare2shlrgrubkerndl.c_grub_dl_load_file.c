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
typedef  scalar_t__ grub_ssize_t ;
typedef  int /*<<< orphan*/ * grub_file_t ;
typedef  TYPE_1__* grub_dl_t ;
struct TYPE_4__ {scalar_t__ ref_count; } ;

/* Variables and functions */
 TYPE_1__* grub_dl_load_core (void*,scalar_t__) ; 
 int /*<<< orphan*/  grub_file_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * grub_file_open (char const*) ; 
 int grub_file_read (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 scalar_t__ grub_file_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  grub_free (void*) ; 
 void* grub_malloc (scalar_t__) ; 

grub_dl_t
grub_dl_load_file (const char *filename)
{
  grub_file_t file = NULL;
  grub_ssize_t size;
  void *core = 0;
  grub_dl_t mod = 0;

  file = grub_file_open (filename);
  if (! file)
    return 0;

  size = grub_file_size (file);
  core = grub_malloc (size);
  if (! core)
    {
      grub_file_close (file);
      return 0;
    }

  if (grub_file_read (file, core, size) != (int) size)
    {
      grub_file_close (file);
      grub_free (core);
      return 0;
    }

  /* We must close this before we try to process dependencies.
     Some disk backends do not handle gracefully multiple concurrent
     opens of the same device.  */
  grub_file_close (file);

  mod = grub_dl_load_core (core, size);
  if (! mod)
    {
      grub_free (core);
      return 0;
    }

  mod->ref_count = 0;
  return mod;
}