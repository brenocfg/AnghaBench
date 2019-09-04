#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_audit_buf {int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {TYPE_1__* signal; } ;
struct TYPE_3__ {int audit_tty; } ;

/* Variables and functions */
 int AUDIT_TTY_ENABLE ; 
 int EPERM ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct tty_audit_buf*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_audit_buf_push (struct tty_audit_buf*) ; 
 struct tty_audit_buf* tty_audit_buf_ref () ; 

int tty_audit_push(void)
{
	struct tty_audit_buf *buf;

	if (~current->signal->audit_tty & AUDIT_TTY_ENABLE)
		return -EPERM;

	buf = tty_audit_buf_ref();
	if (!IS_ERR_OR_NULL(buf)) {
		mutex_lock(&buf->mutex);
		tty_audit_buf_push(buf);
		mutex_unlock(&buf->mutex);
	}
	return 0;
}