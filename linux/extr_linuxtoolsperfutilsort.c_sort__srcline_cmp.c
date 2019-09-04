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
struct hist_entry {void* srcline; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 void* hist_entry__srcline (struct hist_entry*) ; 
 int /*<<< orphan*/  strcmp (void*,void*) ; 

__attribute__((used)) static int64_t
sort__srcline_cmp(struct hist_entry *left, struct hist_entry *right)
{
	if (!left->srcline)
		left->srcline = hist_entry__srcline(left);
	if (!right->srcline)
		right->srcline = hist_entry__srcline(right);

	return strcmp(right->srcline, left->srcline);
}