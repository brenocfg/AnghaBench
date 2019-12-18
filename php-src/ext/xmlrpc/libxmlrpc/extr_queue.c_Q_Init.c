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
struct TYPE_3__ {int /*<<< orphan*/  sorted; scalar_t__ size; int /*<<< orphan*/  head; int /*<<< orphan*/  cursor; int /*<<< orphan*/ * tail; } ;
typedef  TYPE_1__ queue ;

/* Variables and functions */
 int /*<<< orphan*/  False_ ; 
 int True_ ; 

int Q_Init(queue  *q)
{
   if(q) {
      q->head = q->tail = NULL;
      q->cursor = q->head;
      q->size = 0;
      q->sorted = False_;
   }

   return True_;
}