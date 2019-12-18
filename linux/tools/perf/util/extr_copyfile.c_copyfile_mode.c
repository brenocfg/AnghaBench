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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int copyfile_mode_ns (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int copyfile_mode(const char *from, const char *to, mode_t mode)
{
	return copyfile_mode_ns(from, to, mode, NULL);
}