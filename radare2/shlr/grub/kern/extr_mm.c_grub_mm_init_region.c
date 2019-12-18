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
typedef  int grub_size_t ;
typedef  TYPE_1__* grub_mm_region_t ;
typedef  TYPE_2__* grub_mm_header_t ;
struct TYPE_5__ {int size; int /*<<< orphan*/  magic; struct TYPE_5__* next; } ;
struct TYPE_4__ {long addr; int size; struct TYPE_4__* next; TYPE_2__* first; } ;

/* Variables and functions */
 scalar_t__ ALIGN_UP (long,int) ; 
 int GRUB_MM_ALIGN ; 
 int GRUB_MM_ALIGN_LOG2 ; 
 int /*<<< orphan*/  GRUB_MM_FREE_MAGIC ; 
 TYPE_1__* base ; 
 int /*<<< orphan*/  grub_printf (char*,void*,void*) ; 

void
grub_mm_init_region (void *addr, grub_size_t size)
{
  grub_mm_header_t h;
  grub_mm_region_t r, *p, q;

#if 0
  grub_printf ("Using memory for heap: start=%p, end=%p\n", addr, addr + (unsigned int) size);
#endif

  /* Allocate a region from the head.  */
  r = (grub_mm_region_t) ALIGN_UP ((long) addr, GRUB_MM_ALIGN);
  size -= (char *) r - (char *) addr + sizeof (*r);

  /* If this region is too small, ignore it.  */
  if (size < GRUB_MM_ALIGN)
    return;

  h = (grub_mm_header_t) ((char *) r + GRUB_MM_ALIGN);
  h->next = h;
  h->magic = GRUB_MM_FREE_MAGIC;
  h->size = (size >> GRUB_MM_ALIGN_LOG2);

  r->first = h;
  r->addr = (long) h;
  r->size = (h->size << GRUB_MM_ALIGN_LOG2);

  /* Find where to insert this region. Put a smaller one before bigger ones,
     to prevent fragmentation.  */
  for (p = &base, q = *p; q; p = &(q->next), q = *p)
    if (q->size > r->size)
      break;

  *p = r;
  r->next = q;
}