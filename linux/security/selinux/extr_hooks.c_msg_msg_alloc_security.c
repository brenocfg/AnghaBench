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
struct msg_security_struct {int /*<<< orphan*/  sid; } ;
struct msg_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SECINITSID_UNLABELED ; 
 struct msg_security_struct* selinux_msg_msg (struct msg_msg*) ; 

__attribute__((used)) static int msg_msg_alloc_security(struct msg_msg *msg)
{
	struct msg_security_struct *msec;

	msec = selinux_msg_msg(msg);
	msec->sid = SECINITSID_UNLABELED;

	return 0;
}