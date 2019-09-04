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
struct hist_entry {void* srcfile; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 void* hist_entry__get_srcfile (struct hist_entry*) ; 
 int /*<<< orphan*/  strcmp (void*,void*) ; 

__attribute__((used)) static int64_t
sort__srcfile_cmp(struct hist_entry *left, struct hist_entry *right)
{
	if (!left->srcfile)
		left->srcfile = hist_entry__get_srcfile(left);
	if (!right->srcfile)
		right->srcfile = hist_entry__get_srcfile(right);

	return strcmp(right->srcfile, left->srcfile);
}