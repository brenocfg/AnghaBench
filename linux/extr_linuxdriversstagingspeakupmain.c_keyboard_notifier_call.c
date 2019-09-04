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
struct vc_data {scalar_t__ vc_mode; } ;
struct notifier_block {int dummy; } ;
struct keyboard_notifier_param {int value; int /*<<< orphan*/  shift; int /*<<< orphan*/  down; struct vc_data* vc; } ;

/* Variables and functions */
#define  KBD_KEYCODE 137 
#define  KBD_KEYSYM 136 
#define  KBD_POST_KEYSYM 135 
#define  KBD_UNBOUND_KEYCODE 134 
#define  KBD_UNICODE 133 
 scalar_t__ KD_GRAPHICS ; 
 int KTYP (int) ; 
#define  KT_CUR 132 
#define  KT_LATIN 131 
#define  KT_LETTER 130 
#define  KT_SHIFT 129 
#define  KT_SPEC 128 
 unsigned char KVAL (int) ; 
 int NOTIFY_OK ; 
 int NOTIFY_STOP ; 
 int /*<<< orphan*/  do_handle_cursor (struct vc_data*,unsigned char,int) ; 
 int /*<<< orphan*/  do_handle_latin (struct vc_data*,unsigned char,int) ; 
 int /*<<< orphan*/  do_handle_shift (struct vc_data*,unsigned char,int) ; 
 int /*<<< orphan*/  do_handle_spec (struct vc_data*,unsigned char,int) ; 
 int in_keyboard_notifier ; 
 int pre_handle_cursor (struct vc_data*,unsigned char,int) ; 
 scalar_t__ speakup_fake_key_pressed () ; 
 int /*<<< orphan*/  speakup_key (struct vc_data*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int keyboard_notifier_call(struct notifier_block *nb,
				  unsigned long code, void *_param)
{
	struct keyboard_notifier_param *param = _param;
	struct vc_data *vc = param->vc;
	int up = !param->down;
	int ret = NOTIFY_OK;
	static int keycode;	/* to hold the current keycode */

	in_keyboard_notifier = 1;

	if (vc->vc_mode == KD_GRAPHICS)
		goto out;

	/*
	 * First, determine whether we are handling a fake keypress on
	 * the current processor.  If we are, then return NOTIFY_OK,
	 * to pass the keystroke up the chain.  This prevents us from
	 * trying to take the Speakup lock while it is held by the
	 * processor on which the simulated keystroke was generated.
	 * Also, the simulated keystrokes should be ignored by Speakup.
	 */

	if (speakup_fake_key_pressed())
		goto out;

	switch (code) {
	case KBD_KEYCODE:
		/* speakup requires keycode and keysym currently */
		keycode = param->value;
		break;
	case KBD_UNBOUND_KEYCODE:
		/* not used yet */
		break;
	case KBD_UNICODE:
		/* not used yet */
		break;
	case KBD_KEYSYM:
		if (speakup_key(vc, param->shift, keycode, param->value, up))
			ret = NOTIFY_STOP;
		else if (KTYP(param->value) == KT_CUR)
			ret = pre_handle_cursor(vc, KVAL(param->value), up);
		break;
	case KBD_POST_KEYSYM:{
			unsigned char type = KTYP(param->value) - 0xf0;
			unsigned char val = KVAL(param->value);

			switch (type) {
			case KT_SHIFT:
				do_handle_shift(vc, val, up);
				break;
			case KT_LATIN:
			case KT_LETTER:
				do_handle_latin(vc, val, up);
				break;
			case KT_CUR:
				do_handle_cursor(vc, val, up);
				break;
			case KT_SPEC:
				do_handle_spec(vc, val, up);
				break;
			}
			break;
		}
	}
out:
	in_keyboard_notifier = 0;
	return ret;
}