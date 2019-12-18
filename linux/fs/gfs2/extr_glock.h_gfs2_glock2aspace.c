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
struct gfs2_glock {TYPE_1__* gl_ops; } ;
struct address_space {int dummy; } ;
struct TYPE_2__ {int go_flags; } ;

/* Variables and functions */
 int GLOF_ASPACE ; 

__attribute__((used)) static inline struct address_space *gfs2_glock2aspace(struct gfs2_glock *gl)
{
	if (gl->gl_ops->go_flags & GLOF_ASPACE)
		return (struct address_space *)(gl + 1);
	return NULL;
}