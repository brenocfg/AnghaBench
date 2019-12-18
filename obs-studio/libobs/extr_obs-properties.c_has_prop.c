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
struct obs_properties {int dummy; } ;

/* Variables and functions */
 int contains_prop (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  get_topmost_parent (struct obs_properties*) ; 

__attribute__((used)) static inline bool has_prop(struct obs_properties *props, const char *name)
{
	return contains_prop(get_topmost_parent(props), name);
}