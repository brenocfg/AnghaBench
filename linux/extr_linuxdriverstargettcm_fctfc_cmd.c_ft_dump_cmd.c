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
struct ft_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ft_dump_cmd (struct ft_cmd*,char const*) ; 
 int /*<<< orphan*/  ft_debug_logging ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void ft_dump_cmd(struct ft_cmd *cmd, const char *caller)
{
	if (unlikely(ft_debug_logging))
		_ft_dump_cmd(cmd, caller);
}