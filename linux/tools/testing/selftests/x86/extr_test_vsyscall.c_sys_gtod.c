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
 int /*<<< orphan*/  SYS_gettimeofday ; 
 long syscall (int /*<<< orphan*/ ,struct timeval*,struct timezone*) ; 

__attribute__((used)) static inline long sys_gtod(struct timeval *tv, struct timezone *tz)
{
	return syscall(SYS_gettimeofday, tv, tz);
}