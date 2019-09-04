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
 int find_next_bit (unsigned long*,int,int) ; 
 scalar_t__ snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int stringify_nodemap(unsigned long *nodemap, int maxnodes,
			     char *buf, int len)
{
	int out = 0;
	int i = -1;

	while ((i = find_next_bit(nodemap, maxnodes, i + 1)) < maxnodes)
		out += snprintf(buf + out, len - out, "%d ", i);

	return out;
}