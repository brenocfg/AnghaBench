#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* grub_mm_region_t ;
typedef  TYPE_2__* grub_mm_header_t ;
struct TYPE_7__ {scalar_t__ magic; int size; struct TYPE_7__* next; } ;
struct TYPE_6__ {TYPE_2__* first; } ;

/* Variables and functions */
 scalar_t__ GRUB_MM_ALLOC_MAGIC ; 
 scalar_t__ GRUB_MM_FREE_MAGIC ; 
 int /*<<< orphan*/  get_header_from_pointer (void*,TYPE_2__**,TYPE_1__**) ; 
 int /*<<< orphan*/  grub_fatal (char*,TYPE_2__*,scalar_t__) ; 

void
grub_free_orig (void *ptr)
{
    
  grub_mm_header_t p;
  grub_mm_region_t r;

  if (! ptr)
    return;

  get_header_from_pointer (ptr, &p, &r);

  if (r->first->magic == GRUB_MM_ALLOC_MAGIC)
    {
      p->magic = GRUB_MM_FREE_MAGIC;
      r->first = p->next = p;
    }
  else
    {
      grub_mm_header_t q;

#if 0
      q = r->first;
      do
	{
	  grub_printf ("%s:%d: q=%p, q->size=0x%x, q->magic=0x%x\n",
		       GRUB_FILE, __LINE__, q, q->size, q->magic);
	  q = q->next;
	}
      while (q != r->first);
#endif

      for (q = r->first; q >= p || q->next <= p; q = q->next)
	{
	  if (q->magic != GRUB_MM_FREE_MAGIC)
	    grub_fatal ("free magic is broken at %p: 0x%x", q, q->magic);

	  if (q >= q->next && (q < p || q->next > p))
	    break;
	}

      p->magic = GRUB_MM_FREE_MAGIC;
      p->next = q->next;
      q->next = p;

      if (p + p->size == p->next)
	{
	  if (p->next == q)
	    q = p;

	  p->next->magic = 0;
	  p->size += p->next->size;
	  p->next = p->next->next;
	}

      if (q + q->size == p)
	{
	  p->magic = 0;
	  q->size += p->size;
	  q->next = p->next;
	}

      r->first = q;
    }
}