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
struct wspace {int dummy; } ;
struct rs_control {int dummy; } ;

/* Variables and functions */
 int IN_PLACE ; 
 scalar_t__ V_PROGRESS ; 
 int ex_rs_helper (struct rs_control*,struct wspace*,int,int,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ v ; 

__attribute__((used)) static int exercise_rs(struct rs_control *rs, struct wspace *ws,
		       int len, int trials)
{

	int retval = 0;
	int i;

	if (v >= V_PROGRESS)
		pr_info("Testing up to error correction capacity...\n");

	for (i = 0; i <= IN_PLACE; i++)
		retval |= ex_rs_helper(rs, ws, len, trials, i);

	return retval;
}