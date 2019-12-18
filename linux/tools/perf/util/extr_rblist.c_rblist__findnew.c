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
struct rblist {int dummy; } ;
struct rb_node {int dummy; } ;

/* Variables and functions */
 struct rb_node* __rblist__findnew (struct rblist*,void const*,int) ; 

struct rb_node *rblist__findnew(struct rblist *rblist, const void *entry)
{
	return __rblist__findnew(rblist, entry, true);
}