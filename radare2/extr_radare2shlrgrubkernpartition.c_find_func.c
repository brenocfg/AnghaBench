#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct find_func_closure {scalar_t__ partnum; TYPE_1__* p; } ;
typedef  TYPE_1__* grub_partition_t ;
typedef  int /*<<< orphan*/  grub_disk_t ;
struct TYPE_5__ {scalar_t__ number; } ;

/* Variables and functions */
 scalar_t__ grub_malloc (int) ; 
 int /*<<< orphan*/  grub_memcpy (TYPE_1__*,TYPE_1__* const,int) ; 

__attribute__((used)) static int
find_func (grub_disk_t d ,
	   const grub_partition_t partition, void *closure)
{
  struct find_func_closure *c = closure;
  if (c->partnum == partition->number)
    {
      c->p = (grub_partition_t) grub_malloc (sizeof (*c->p));
      if (! c->p)
	return 1;

      grub_memcpy (c->p, partition, sizeof (*c->p));
      return 1;
    }

  return 0;
}