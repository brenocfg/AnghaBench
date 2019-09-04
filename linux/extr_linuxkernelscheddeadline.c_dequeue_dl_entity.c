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
struct sched_dl_entity {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dequeue_dl_entity (struct sched_dl_entity*) ; 

__attribute__((used)) static void dequeue_dl_entity(struct sched_dl_entity *dl_se)
{
	__dequeue_dl_entity(dl_se);
}