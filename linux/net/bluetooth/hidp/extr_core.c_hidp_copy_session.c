#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct hidp_session {int flags; TYPE_3__* hid; TYPE_2__* input; int /*<<< orphan*/  bdaddr; } ;
struct hidp_conninfo {int flags; int /*<<< orphan*/  name; int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  state; int /*<<< orphan*/  bdaddr; } ;
struct TYPE_6__ {char* name; int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; } ;
struct TYPE_4__ {int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; } ;
struct TYPE_5__ {char* name; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CONNECTED ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct hidp_conninfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void hidp_copy_session(struct hidp_session *session, struct hidp_conninfo *ci)
{
	u32 valid_flags = 0;
	memset(ci, 0, sizeof(*ci));
	bacpy(&ci->bdaddr, &session->bdaddr);

	ci->flags = session->flags & valid_flags;
	ci->state = BT_CONNECTED;

	if (session->input) {
		ci->vendor  = session->input->id.vendor;
		ci->product = session->input->id.product;
		ci->version = session->input->id.version;
		if (session->input->name)
			strlcpy(ci->name, session->input->name, 128);
		else
			strlcpy(ci->name, "HID Boot Device", 128);
	} else if (session->hid) {
		ci->vendor  = session->hid->vendor;
		ci->product = session->hid->product;
		ci->version = session->hid->version;
		strlcpy(ci->name, session->hid->name, 128);
	}
}