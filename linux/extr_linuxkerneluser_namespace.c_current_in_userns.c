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
struct user_namespace {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_user_ns () ; 
 int in_userns (struct user_namespace const*,int /*<<< orphan*/ ) ; 

bool current_in_userns(const struct user_namespace *target_ns)
{
	return in_userns(target_ns, current_user_ns());
}