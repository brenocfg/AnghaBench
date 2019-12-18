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
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  recalculate_transition_matrix (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void recalculate_transition_matrices(obs_source_t *transition)
{
	recalculate_transition_matrix(transition, 0);
	recalculate_transition_matrix(transition, 1);
}