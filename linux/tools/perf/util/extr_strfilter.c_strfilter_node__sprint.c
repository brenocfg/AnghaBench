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
struct strfilter_node {int* p; int /*<<< orphan*/  r; int /*<<< orphan*/  l; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __fallthrough ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strfilter_node__sprint_pt (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int strfilter_node__sprint(struct strfilter_node *node, char *buf)
{
	int len = 0, rlen;

	if (!node || !node->p)
		return -EINVAL;

	switch (*node->p) {
	case '|':
	case '&':
		len = strfilter_node__sprint_pt(node->l, buf);
		if (len < 0)
			return len;
		__fallthrough;
	case '!':
		if (buf) {
			*(buf + len++) = *node->p;
			buf += len;
		} else
			len++;
		rlen = strfilter_node__sprint_pt(node->r, buf);
		if (rlen < 0)
			return rlen;
		len += rlen;
		break;
	default:
		len = strlen(node->p);
		if (buf)
			strcpy(buf, node->p);
	}

	return len;
}