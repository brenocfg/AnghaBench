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
typedef  int /*<<< orphan*/  obs_properties_t ;

/* Variables and functions */
 int /*<<< orphan*/ * obs_properties_get_parent (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline obs_properties_t *get_topmost_parent(obs_properties_t *props)
{
	obs_properties_t *parent = props;
	obs_properties_t *last_parent = parent;
	while (parent) {
		last_parent = parent;
		parent = obs_properties_get_parent(parent);
	}
	return last_parent;
}