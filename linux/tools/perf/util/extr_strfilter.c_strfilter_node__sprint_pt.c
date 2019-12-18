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
struct strfilter_node {scalar_t__ r; } ;

/* Variables and functions */
 int strfilter_node__sprint (struct strfilter_node*,char*) ; 

__attribute__((used)) static int strfilter_node__sprint_pt(struct strfilter_node *node, char *buf)
{
	int len;
	int pt = node->r ? 2 : 0;	/* don't need to check node->l */

	if (buf && pt)
		*buf++ = '(';
	len = strfilter_node__sprint(node, buf);
	if (len < 0)
		return len;
	if (buf && pt)
		*(buf + len) = ')';
	return len + pt;
}