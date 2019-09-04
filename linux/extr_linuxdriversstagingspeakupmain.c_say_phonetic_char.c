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
typedef  int /*<<< orphan*/  u_short ;
typedef  int u16 ;
struct vc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_NUM ; 
 scalar_t__ IS_CHAR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_NUMBER ; 
 int get_char (struct vc_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ isalpha (int) ; 
 int /*<<< orphan*/ * phonetic ; 
 int /*<<< orphan*/  speak_char (int) ; 
 int /*<<< orphan*/  spk_attr ; 
 int /*<<< orphan*/  spk_msg_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spk_old_attr ; 
 scalar_t__ spk_pos ; 
 int /*<<< orphan*/  synth_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void say_phonetic_char(struct vc_data *vc)
{
	u16 ch;

	spk_old_attr = spk_attr;
	ch = get_char(vc, (u_short *)spk_pos, &spk_attr);
	if (ch <= 0x7f && isalpha(ch)) {
		ch &= 0x1f;
		synth_printf("%s\n", phonetic[--ch]);
	} else {
		if (ch < 0x100 && IS_CHAR(ch, B_NUM))
			synth_printf("%s ", spk_msg_get(MSG_NUMBER));
		speak_char(ch);
	}
}