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

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int capable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool may_mandlock(void)
{
#ifndef	CONFIG_MANDATORY_FILE_LOCKING
	return false;
#endif
	return capable(CAP_SYS_ADMIN);
}