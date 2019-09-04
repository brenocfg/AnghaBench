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
struct gcov_iterator {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct gcov_iterator*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

void gcov_iter_free(struct gcov_iterator *iter)
{
	vfree(iter->buffer);
	kfree(iter);
}