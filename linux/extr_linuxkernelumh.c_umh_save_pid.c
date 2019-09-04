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
struct umh_info {int /*<<< orphan*/  pid; } ;
struct subprocess_info {int /*<<< orphan*/  pid; struct umh_info* data; } ;

/* Variables and functions */

__attribute__((used)) static void umh_save_pid(struct subprocess_info *info)
{
	struct umh_info *umh_info = info->data;

	umh_info->pid = info->pid;
}