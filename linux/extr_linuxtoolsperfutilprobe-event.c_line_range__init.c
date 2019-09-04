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
struct line_range {int /*<<< orphan*/  line_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  intlist__new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct line_range*,int /*<<< orphan*/ ,int) ; 

int line_range__init(struct line_range *lr)
{
	memset(lr, 0, sizeof(*lr));
	lr->line_list = intlist__new(NULL);
	if (!lr->line_list)
		return -ENOMEM;
	else
		return 0;
}