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
typedef  int grub_size_t ;
typedef  TYPE_1__* grub_mm_region_t ;
struct TYPE_3__ {int /*<<< orphan*/  first; struct TYPE_3__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_OUT_OF_MEMORY ; 
 int GRUB_MM_ALIGN ; 
 int GRUB_MM_ALIGN_LOG2 ; 
 TYPE_1__* base ; 
 int /*<<< orphan*/  grub_disk_cache_invalidate_all () ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 void* grub_real_malloc (int /*<<< orphan*/ *,int,int) ; 

void *
grub_memalign (grub_size_t align, grub_size_t size)
{
  grub_mm_region_t r;
  grub_size_t n = ((size + GRUB_MM_ALIGN - 1) >> GRUB_MM_ALIGN_LOG2) + 1;
  int count = 0;

  align = (align >> GRUB_MM_ALIGN_LOG2);
  if (align == 0)
    align = 1;

 again:

  for (r = base; r; r = r->next)
    {
      void *p;

      p = grub_real_malloc (&(r->first), n, align);
      if (p)
	return p;
    }

  /* If failed, increase free memory somehow.  */
  switch (count)
    {
    case 0:
      /* Invalidate disk caches.  */
      grub_disk_cache_invalidate_all ();
      count++;
      goto again;

    case 1:
      /* Unload unneeded modules.  */
      //grub_dl_unload_unneeded ();
      count++;
      goto again;

    default:
      break;
    }

  grub_error (GRUB_ERR_OUT_OF_MEMORY, "out of memory");
  return 0;
}