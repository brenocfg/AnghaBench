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

/* Variables and functions */
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_internal (char*,char*) ; 
 int /*<<< orphan*/  errmsg_internal (char*,char const*) ; 
 char* format_node_dump (char*) ; 
 char* nodeToString (void const*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* pretty_format_node_dump (char*) ; 

void
elog_node_display(int lev, const char *title, const void *obj, bool pretty)
{
	char	   *s;
	char	   *f;

	s = nodeToString(obj);
	if (pretty)
		f = pretty_format_node_dump(s);
	else
		f = format_node_dump(s);
	pfree(s);
	ereport(lev,
			(errmsg_internal("%s:", title),
			 errdetail_internal("%s", f)));
	pfree(f);
}