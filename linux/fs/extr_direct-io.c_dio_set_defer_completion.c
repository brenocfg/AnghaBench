#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_dio_done_wq; } ;
struct dio {int defer_completion; TYPE_1__* inode; } ;
struct TYPE_2__ {struct super_block* i_sb; } ;

/* Variables and functions */
 int sb_init_dio_done_wq (struct super_block*) ; 

__attribute__((used)) static int dio_set_defer_completion(struct dio *dio)
{
	struct super_block *sb = dio->inode->i_sb;

	if (dio->defer_completion)
		return 0;
	dio->defer_completion = true;
	if (!sb->s_dio_done_wq)
		return sb_init_dio_done_wq(sb);
	return 0;
}