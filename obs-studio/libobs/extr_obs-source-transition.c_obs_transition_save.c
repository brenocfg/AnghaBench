#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* name; } ;
struct TYPE_8__ {int /*<<< orphan*/  transition_cy; int /*<<< orphan*/  transition_cx; scalar_t__ transition_scale_type; scalar_t__ transition_mode; int /*<<< orphan*/  transition_alignment; TYPE_1__ context; struct TYPE_8__** transition_sources; } ;
typedef  TYPE_2__ obs_source_t ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  lock_transition (TYPE_2__*) ; 
 int /*<<< orphan*/  obs_data_set_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_data_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ transition_active (TYPE_2__*) ; 
 int /*<<< orphan*/  unlock_transition (TYPE_2__*) ; 

void obs_transition_save(obs_source_t *tr, obs_data_t *data)
{
	obs_source_t *child;

	lock_transition(tr);
	child = transition_active(tr) ? tr->transition_sources[1]
				      : tr->transition_sources[0];

	obs_data_set_string(data, "transition_source_a",
			    child ? child->context.name : "");
	obs_data_set_int(data, "transition_alignment",
			 tr->transition_alignment);
	obs_data_set_int(data, "transition_mode", (int64_t)tr->transition_mode);
	obs_data_set_int(data, "transition_scale_type",
			 (int64_t)tr->transition_scale_type);
	obs_data_set_int(data, "transition_cx", tr->transition_cx);
	obs_data_set_int(data, "transition_cy", tr->transition_cy);
	unlock_transition(tr);
}