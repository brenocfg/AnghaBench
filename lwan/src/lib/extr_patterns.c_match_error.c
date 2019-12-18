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
struct match_state {char const* error; } ;

/* Variables and functions */

__attribute__((used)) static int
match_error(struct match_state *ms, const char *error)
{
	ms->error = ms->error == NULL ? error : ms->error;
	return (-1);
}