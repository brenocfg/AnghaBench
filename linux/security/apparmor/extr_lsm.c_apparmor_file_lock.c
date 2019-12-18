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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_MAY_LOCK ; 
 unsigned int F_WRLCK ; 
 int /*<<< orphan*/  MAY_WRITE ; 
 int /*<<< orphan*/  OP_FLOCK ; 
 int common_file_perm (int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apparmor_file_lock(struct file *file, unsigned int cmd)
{
	u32 mask = AA_MAY_LOCK;

	if (cmd == F_WRLCK)
		mask |= MAY_WRITE;

	return common_file_perm(OP_FLOCK, file, mask);
}