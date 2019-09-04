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
struct timezone {int dummy; } ;
struct timeval {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __NR_gettimeofday ; 
 int syscall (int /*<<< orphan*/ ,struct timeval*,struct timezone*) ; 

__attribute__((used)) static inline int sys_gettimeofday(struct timeval *tv, struct timezone *tz)
{
	return syscall(__NR_gettimeofday, tv, tz);
}