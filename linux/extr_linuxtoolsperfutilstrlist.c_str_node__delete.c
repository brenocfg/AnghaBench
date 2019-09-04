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
struct str_node {int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct str_node*) ; 
 int /*<<< orphan*/  zfree (char**) ; 

__attribute__((used)) static void str_node__delete(struct str_node *snode, bool dupstr)
{
	if (dupstr)
		zfree((char **)&snode->s);
	free(snode);
}