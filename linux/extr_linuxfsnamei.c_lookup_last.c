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
struct TYPE_2__ {size_t len; scalar_t__* name; } ;
struct nameidata {scalar_t__ last_type; int flags; TYPE_1__ last; } ;

/* Variables and functions */
 scalar_t__ LAST_NORM ; 
 int LOOKUP_DIRECTORY ; 
 int LOOKUP_FOLLOW ; 
 int LOOKUP_PARENT ; 
 int walk_component (struct nameidata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int lookup_last(struct nameidata *nd)
{
	if (nd->last_type == LAST_NORM && nd->last.name[nd->last.len])
		nd->flags |= LOOKUP_FOLLOW | LOOKUP_DIRECTORY;

	nd->flags &= ~LOOKUP_PARENT;
	return walk_component(nd, 0);
}