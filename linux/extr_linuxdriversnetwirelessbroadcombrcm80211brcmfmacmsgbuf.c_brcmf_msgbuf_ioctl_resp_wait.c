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
struct brcmf_msgbuf {int /*<<< orphan*/  ctl_completed; int /*<<< orphan*/  ioctl_resp_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGBUF_IOCTL_RESP_TIMEOUT ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_msgbuf_ioctl_resp_wait(struct brcmf_msgbuf *msgbuf)
{
	return wait_event_timeout(msgbuf->ioctl_resp_wait,
				  msgbuf->ctl_completed,
				  MSGBUF_IOCTL_RESP_TIMEOUT);
}