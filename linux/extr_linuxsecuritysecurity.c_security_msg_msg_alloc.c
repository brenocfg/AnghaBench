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
struct msg_msg {int dummy; } ;

/* Variables and functions */
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct msg_msg*) ; 
 int /*<<< orphan*/  msg_msg_alloc_security ; 

int security_msg_msg_alloc(struct msg_msg *msg)
{
	return call_int_hook(msg_msg_alloc_security, 0, msg);
}