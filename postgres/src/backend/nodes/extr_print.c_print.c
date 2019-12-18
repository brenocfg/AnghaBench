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
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* format_node_dump (char*) ; 
 char* nodeToString (void const*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stdout ; 

void
print(const void *obj)
{
	char	   *s;
	char	   *f;

	s = nodeToString(obj);
	f = format_node_dump(s);
	pfree(s);
	printf("%s\n", f);
	fflush(stdout);
	pfree(f);
}