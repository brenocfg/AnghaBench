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
struct smsg_app_event {struct smsg_app_event* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct smsg_app_event*) ; 

__attribute__((used)) static void smsg_app_event_free(struct smsg_app_event *ev)
{
	kfree(ev->buf);
	kfree(ev);
}