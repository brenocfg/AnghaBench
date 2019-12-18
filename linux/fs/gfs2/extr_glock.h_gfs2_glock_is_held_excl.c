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
struct gfs2_glock {scalar_t__ gl_state; } ;

/* Variables and functions */
 scalar_t__ LM_ST_EXCLUSIVE ; 

__attribute__((used)) static inline int gfs2_glock_is_held_excl(struct gfs2_glock *gl)
{
	return gl->gl_state == LM_ST_EXCLUSIVE;
}