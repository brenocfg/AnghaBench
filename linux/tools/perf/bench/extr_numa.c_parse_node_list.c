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
struct TYPE_2__ {int /*<<< orphan*/  node_list_str; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ p0 ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static int parse_node_list(const char *arg)
{
	p0.node_list_str = strdup(arg);

	dprintf("got NODE list: {%s}\n", p0.node_list_str);

	return 0;
}