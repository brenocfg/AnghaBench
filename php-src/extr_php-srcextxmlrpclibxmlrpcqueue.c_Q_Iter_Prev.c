#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * q_iter ;
struct TYPE_2__ {scalar_t__ prev; } ;
typedef  TYPE_1__ node ;

/* Variables and functions */

q_iter Q_Iter_Prev(q_iter qi) {
   return qi ? (q_iter)((node*)qi)->prev : NULL;
}