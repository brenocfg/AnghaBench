#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* robustMxList; } ;
typedef  TYPE_1__ ptw32_thread_t ;
struct TYPE_8__ {struct TYPE_8__* prev; struct TYPE_8__* next; } ;
typedef  TYPE_2__ ptw32_robust_node_t ;
struct TYPE_9__ {scalar_t__ p; } ;
typedef  TYPE_3__ pthread_t ;
typedef  TYPE_4__* pthread_mutex_t ;
struct TYPE_10__ {TYPE_3__ ownerThread; TYPE_2__* robustNode; } ;

/* Variables and functions */

void
ptw32_robust_mutex_add(pthread_mutex_t* mutex, pthread_t self)
{
  ptw32_robust_node_t** list;
  pthread_mutex_t mx = *mutex;
  ptw32_thread_t* tp = (ptw32_thread_t*)self.p;
  ptw32_robust_node_t* robust = mx->robustNode;

  list = &tp->robustMxList;
  mx->ownerThread = self;
  if (NULL == *list)
    {
      robust->prev = NULL;
      robust->next = NULL;
      *list = robust;
    }
  else
    {
      robust->prev = NULL;
      robust->next = *list;
      (*list)->prev = robust;
      *list = robust;
    }
}