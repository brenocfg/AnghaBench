#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xcb_keycode_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct dstr {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  root; int /*<<< orphan*/  window; scalar_t__ keycode; int /*<<< orphan*/  display; int /*<<< orphan*/  type; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ XKeyEvent ;
struct TYPE_6__ {TYPE_3__* platform_context; } ;
struct TYPE_9__ {TYPE_1__ hotkeys; } ;
struct TYPE_8__ {int /*<<< orphan*/  display; } ;

/* Variables and functions */
 int /*<<< orphan*/  KeyPress ; 
 int /*<<< orphan*/ * XGetXCBConnection (int /*<<< orphan*/ ) ; 
 int XLookupString (TYPE_2__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dstr_ncopy (struct dstr*,char*,int) ; 
 int /*<<< orphan*/  dstr_to_upper (struct dstr*) ; 
 TYPE_4__* obs ; 
 int /*<<< orphan*/  root_window (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool get_key_translation(struct dstr *dstr, xcb_keycode_t keycode)
{
	xcb_connection_t *connection;
	char name[128];

	connection = XGetXCBConnection(obs->hotkeys.platform_context->display);

	XKeyEvent event = {0};
	event.type = KeyPress;
	event.display = obs->hotkeys.platform_context->display;
	event.keycode = keycode;
	event.root = root_window(obs->hotkeys.platform_context, connection);
	event.window = event.root;

	if (keycode) {
		int len = XLookupString(&event, name, 128, NULL, NULL);
		if (len) {
			dstr_ncopy(dstr, name, len);
			dstr_to_upper(dstr);
			return true;
		}
	}

	return false;
}