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
struct hidp_session {scalar_t__ input; TYPE_1__* hid; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int hid_add_device (TYPE_1__*) ; 
 int /*<<< orphan*/  input_get_device (scalar_t__) ; 
 int input_register_device (scalar_t__) ; 

__attribute__((used)) static int hidp_session_dev_add(struct hidp_session *session)
{
	int ret;

	/* Both HID and input systems drop a ref-count when unregistering the
	 * device but they don't take a ref-count when registering them. Work
	 * around this by explicitly taking a refcount during registration
	 * which is dropped automatically by unregistering the devices. */

	if (session->hid) {
		ret = hid_add_device(session->hid);
		if (ret)
			return ret;
		get_device(&session->hid->dev);
	} else if (session->input) {
		ret = input_register_device(session->input);
		if (ret)
			return ret;
		input_get_device(session->input);
	}

	return 0;
}