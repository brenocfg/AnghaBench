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
typedef  int /*<<< orphan*/  u32 ;
struct kstat {int /*<<< orphan*/  rdev; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ vfs_stat (char*,struct kstat*) ; 

__attribute__((used)) static inline u32 bstat(char *name)
{
	struct kstat stat;
	if (vfs_stat(name, &stat) != 0)
		return 0;
	if (!S_ISBLK(stat.mode))
		return 0;
	return stat.rdev;
}