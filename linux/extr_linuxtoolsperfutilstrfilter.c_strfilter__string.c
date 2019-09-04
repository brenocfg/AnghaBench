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
struct strfilter {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 char* malloc (int) ; 
 int strfilter_node__sprint (int /*<<< orphan*/ ,char*) ; 

char *strfilter__string(struct strfilter *filter)
{
	int len;
	char *ret = NULL;

	len = strfilter_node__sprint(filter->root, NULL);
	if (len < 0)
		return NULL;

	ret = malloc(len + 1);
	if (ret)
		strfilter_node__sprint(filter->root, ret);

	return ret;
}