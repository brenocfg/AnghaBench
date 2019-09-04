#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  queue ;

/* Variables and functions */
 int /*<<< orphan*/  Q_IsEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Q_PopHead (int /*<<< orphan*/ *) ; 

void Q_Destroy(queue *q)
{
   while(!Q_IsEmpty(q)) {
      Q_PopHead(q);
   }
}