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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_EXECUTE_READWRITE ; 
 int /*<<< orphan*/  VirtualProtect (void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void fix_permissions(void *addr, size_t size)
{
	DWORD protect_val;
	VirtualProtect(addr, size, PAGE_EXECUTE_READWRITE, &protect_val);
}