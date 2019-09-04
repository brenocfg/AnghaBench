#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  memory_data; TYPE_3__* (* malloc ) (unsigned int,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int heap_limit; scalar_t__ heap_used; TYPE_1__ memctl; } ;
typedef  TYPE_2__ dfa_match_block ;
struct TYPE_9__ {int size; unsigned int free; struct TYPE_9__* next; } ;
typedef  TYPE_3__ RWS_anchor ;

/* Variables and functions */
 int PCRE2_ERROR_HEAPLIMIT ; 
 int PCRE2_ERROR_NOMEMORY ; 
 unsigned int RWS_ANCHOR_SIZE ; 
 unsigned int RWS_RSIZE ; 
 TYPE_3__* stub1 (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
more_workspace(RWS_anchor **rwsptr, unsigned int ovecsize, dfa_match_block *mb)
{
RWS_anchor *rws = *rwsptr;
RWS_anchor *new;

if (rws->next != NULL)
  {
  new = rws->next;
  }

/* All sizes are in units of sizeof(int), except for mb->heaplimit, which is in
kibibytes. */

else
  {
  unsigned int newsize = rws->size * 2;
  unsigned int heapleft = (unsigned int)
    (((1024/sizeof(int))*mb->heap_limit - mb->heap_used));
  if (newsize > heapleft) newsize = heapleft;
  if (newsize < RWS_RSIZE + ovecsize + RWS_ANCHOR_SIZE)
    return PCRE2_ERROR_HEAPLIMIT;
  new = mb->memctl.malloc(newsize*sizeof(int), mb->memctl.memory_data);
  if (new == NULL) return PCRE2_ERROR_NOMEMORY;
  mb->heap_used += newsize;
  new->next = NULL;
  new->size = newsize;
  rws->next = new;
  }

new->free = new->size - RWS_ANCHOR_SIZE;
*rwsptr = new;
return 0;
}