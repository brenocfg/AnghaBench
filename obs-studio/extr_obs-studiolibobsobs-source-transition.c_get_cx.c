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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ transition_actual_cx; scalar_t__ transition_cx; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t get_cx(obs_source_t *tr)
{
	return tr->transition_cx ?
		tr->transition_cx : tr->transition_actual_cx;
}