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
struct key {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  KEY_FLAG_USER_CONSTRUCT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int key_read_state (struct key*) ; 
 int key_validate (struct key*) ; 
 int wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wait_for_key_construction(struct key *key, bool intr)
{
	int ret;

	ret = wait_on_bit(&key->flags, KEY_FLAG_USER_CONSTRUCT,
			  intr ? TASK_INTERRUPTIBLE : TASK_UNINTERRUPTIBLE);
	if (ret)
		return -ERESTARTSYS;
	ret = key_read_state(key);
	if (ret < 0)
		return ret;
	return key_validate(key);
}