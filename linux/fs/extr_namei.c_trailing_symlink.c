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
struct nameidata {TYPE_1__* stack; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 char const* ERR_PTR (int) ; 
 int /*<<< orphan*/  LOOKUP_PARENT ; 
 char* get_link (struct nameidata*) ; 
 int may_follow_link (struct nameidata*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static const char *trailing_symlink(struct nameidata *nd)
{
	const char *s;
	int error = may_follow_link(nd);
	if (unlikely(error))
		return ERR_PTR(error);
	nd->flags |= LOOKUP_PARENT;
	nd->stack[0].name = NULL;
	s = get_link(nd);
	return s ? s : "";
}