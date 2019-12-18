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
struct path {int dummy; } ;

/* Variables and functions */
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct path const*,struct path const*) ; 
 int /*<<< orphan*/  move_mount ; 

int security_move_mount(const struct path *from_path, const struct path *to_path)
{
	return call_int_hook(move_mount, 0, from_path, to_path);
}