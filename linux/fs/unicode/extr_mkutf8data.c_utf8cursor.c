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
struct utf8cursor {int dummy; } ;
struct tree {int dummy; } ;

/* Variables and functions */
 int utf8ncursor (struct utf8cursor*,struct tree*,char const*,unsigned int) ; 

int utf8cursor(struct utf8cursor *u8c, struct tree *tree, const char *s)
{
	return utf8ncursor(u8c, tree, s, (unsigned int)-1);
}