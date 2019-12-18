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
struct line_range {int /*<<< orphan*/  line_list; int /*<<< orphan*/  comp_dir; int /*<<< orphan*/  path; int /*<<< orphan*/  file; int /*<<< orphan*/  function; } ;

/* Variables and functions */
 int /*<<< orphan*/  intlist__delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

void line_range__clear(struct line_range *lr)
{
	zfree(&lr->function);
	zfree(&lr->file);
	zfree(&lr->path);
	zfree(&lr->comp_dir);
	intlist__delete(lr->line_list);
}