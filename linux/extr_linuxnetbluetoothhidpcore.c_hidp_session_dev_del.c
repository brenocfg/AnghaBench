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
struct hidp_session {scalar_t__ input; scalar_t__ hid; } ;

/* Variables and functions */
 int /*<<< orphan*/  hid_destroy_device (scalar_t__) ; 
 int /*<<< orphan*/  input_unregister_device (scalar_t__) ; 

__attribute__((used)) static void hidp_session_dev_del(struct hidp_session *session)
{
	if (session->hid)
		hid_destroy_device(session->hid);
	else if (session->input)
		input_unregister_device(session->input);
}