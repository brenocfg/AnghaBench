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
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int w32_GetProcessId (scalar_t__) ; 
 int w32_GetThreadId (scalar_t__) ; 

__attribute__((used)) inline static int w32_h2t(HANDLE h) {
	if (w32_GetThreadId != NULL) // >= Windows Vista
		return w32_GetThreadId (h);
	if (w32_GetProcessId != NULL) // >= Windows XP1
		return w32_GetProcessId (h);
	return (int)(size_t)h; // XXX broken
}