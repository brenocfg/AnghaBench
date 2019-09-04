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
typedef  int /*<<< orphan*/  PARAMDSC ;

/* Variables and functions */
 int /*<<< orphan*/  call_php (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 

void udf_call_php2(char *name, PARAMDSC *r, PARAMDSC *arg1, PARAMDSC *arg2)
{
	PARAMDSC *args[2] = { arg1, arg2 };
	call_php(name, r, 2, args);
}