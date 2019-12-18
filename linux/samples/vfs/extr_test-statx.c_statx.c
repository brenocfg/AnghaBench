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
struct statx {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  __NR_statx ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int,char const*,unsigned int,unsigned int,struct statx*) ; 

__attribute__((used)) static __attribute__((unused))
ssize_t statx(int dfd, const char *filename, unsigned flags,
	      unsigned int mask, struct statx *buffer)
{
	return syscall(__NR_statx, dfd, filename, flags, mask, buffer);
}