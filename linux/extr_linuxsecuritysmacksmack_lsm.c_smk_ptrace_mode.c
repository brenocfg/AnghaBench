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
 unsigned int MAY_READ ; 
 unsigned int MAY_READWRITE ; 
 unsigned int PTRACE_MODE_ATTACH ; 
 unsigned int PTRACE_MODE_READ ; 

__attribute__((used)) static inline unsigned int smk_ptrace_mode(unsigned int mode)
{
	if (mode & PTRACE_MODE_ATTACH)
		return MAY_READWRITE;
	if (mode & PTRACE_MODE_READ)
		return MAY_READ;

	return 0;
}