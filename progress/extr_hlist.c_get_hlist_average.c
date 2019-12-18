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
struct TYPE_3__ {struct TYPE_3__* next; scalar_t__ value; } ;
typedef  TYPE_1__ hlist ;

/* Variables and functions */

int get_hlist_average(hlist *begin, int size) {
   unsigned long long avg = 0;

   while (begin) {
      avg += begin->value;
      begin = begin->next;
   }
   return avg / size;
}