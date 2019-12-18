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
struct sched_dl_entity {int /*<<< orphan*/  dl_bw; } ;
struct dl_rq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __add_rq_bw (int /*<<< orphan*/ ,struct dl_rq*) ; 
 int /*<<< orphan*/  dl_entity_is_special (struct sched_dl_entity*) ; 

__attribute__((used)) static inline
void add_rq_bw(struct sched_dl_entity *dl_se, struct dl_rq *dl_rq)
{
	if (!dl_entity_is_special(dl_se))
		__add_rq_bw(dl_se->dl_bw, dl_rq);
}