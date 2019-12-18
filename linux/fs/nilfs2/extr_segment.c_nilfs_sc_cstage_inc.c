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
struct TYPE_2__ {int /*<<< orphan*/  scnt; } ;
struct nilfs_sc_info {TYPE_1__ sc_stage; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_nilfs2_collection_stage_transition (struct nilfs_sc_info*) ; 

__attribute__((used)) static inline void nilfs_sc_cstage_inc(struct nilfs_sc_info *sci)
{
	sci->sc_stage.scnt++;
	trace_nilfs2_collection_stage_transition(sci);
}