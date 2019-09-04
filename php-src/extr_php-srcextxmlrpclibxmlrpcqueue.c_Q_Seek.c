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
struct TYPE_5__ {int /*<<< orphan*/  cursor; int /*<<< orphan*/  sorted; } ;
typedef  TYPE_1__ queue ;

/* Variables and functions */
 int Q_BSearch (TYPE_1__*,void*,int (*) (void const*,void const*)) ; 
 int /*<<< orphan*/  Q_Sort (TYPE_1__*,int (*) (void const*,void const*)) ; 
 void** queue_index ; 
 int /*<<< orphan*/ * queue_posn_index ; 

void *Q_Seek(queue *q, void *data, int (*Comp)(const void *, const void *))
{
   int idx;

   if (q == NULL) {
	return NULL;
   }

   if(!q->sorted) {
      if(!Q_Sort(q, Comp))
         return NULL;
   }

   idx = Q_BSearch(q, data, Comp);

   if(idx < 0)
      return NULL;

   q->cursor = queue_posn_index[idx];

   return queue_index[idx];
}