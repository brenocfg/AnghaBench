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
struct TYPE_2__ {scalar_t__ frozen; int /*<<< orphan*/  wait_unfrozen; } ;
struct super_block {TYPE_1__ s_writers; int /*<<< orphan*/  s_umount; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SB_UNFROZEN ; 
 struct super_block* __get_super (struct block_device*,int) ; 
 int /*<<< orphan*/  put_super (struct super_block*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct super_block *__get_super_thawed(struct block_device *bdev,
					      bool excl)
{
	while (1) {
		struct super_block *s = __get_super(bdev, excl);
		if (!s || s->s_writers.frozen == SB_UNFROZEN)
			return s;
		if (!excl)
			up_read(&s->s_umount);
		else
			up_write(&s->s_umount);
		wait_event(s->s_writers.wait_unfrozen,
			   s->s_writers.frozen == SB_UNFROZEN);
		put_super(s);
	}
}