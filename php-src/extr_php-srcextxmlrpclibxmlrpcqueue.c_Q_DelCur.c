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
struct TYPE_4__ {scalar_t__ cursor; } ;
typedef  TYPE_1__ queue ;
typedef  int /*<<< orphan*/  q_iter ;

/* Variables and functions */
 void* Q_Iter_Del (TYPE_1__*,int /*<<< orphan*/ ) ; 

void *Q_DelCur(queue* q) {
   if(q) {
      return Q_Iter_Del(q, (q_iter)q->cursor);
   }
   return 0;
}