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
struct cred {TYPE_1__* thread_keyring; int /*<<< orphan*/  fsgid; } ;
struct TYPE_2__ {int /*<<< orphan*/  sem; int /*<<< orphan*/  gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void key_fsgid_changed(struct cred *new_cred)
{
	/* update the ownership of the thread keyring */
	if (new_cred->thread_keyring) {
		down_write(&new_cred->thread_keyring->sem);
		new_cred->thread_keyring->gid = new_cred->fsgid;
		up_write(&new_cred->thread_keyring->sem);
	}
}