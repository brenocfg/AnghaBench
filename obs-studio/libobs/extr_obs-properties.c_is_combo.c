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
struct obs_property {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ OBS_PROPERTY_LIST ; 

__attribute__((used)) static inline bool is_combo(struct obs_property *p)
{
	return p->type == OBS_PROPERTY_LIST;
}