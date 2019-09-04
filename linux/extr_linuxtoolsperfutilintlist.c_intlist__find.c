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
struct intlist {int dummy; } ;
struct int_node {int dummy; } ;

/* Variables and functions */
 struct int_node* __intlist__findnew (struct intlist*,int,int) ; 

struct int_node *intlist__find(struct intlist *ilist, int i)
{
	return __intlist__findnew(ilist, i, false);
}