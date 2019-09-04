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
struct hidp_session {int /*<<< orphan*/ * rd_data; scalar_t__ input; TYPE_1__* hid; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_put_device (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hidp_session_dev_destroy(struct hidp_session *session)
{
	if (session->hid)
		put_device(&session->hid->dev);
	else if (session->input)
		input_put_device(session->input);

	kfree(session->rd_data);
	session->rd_data = NULL;
}