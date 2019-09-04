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
typedef  int /*<<< orphan*/  u_short ;
typedef  size_t u_char ;
struct vc_data {int dummy; } ;
struct TYPE_2__ {short mask; } ;

/* Variables and functions */
 short B_NUM ; 
 size_t KT_LATIN ; 
 int /*<<< orphan*/  MSG_EDIT_DONE ; 
 int /*<<< orphan*/  MSG_OFF ; 
 int /*<<< orphan*/  MSG_ON ; 
 short PUNC ; 
 size_t SPACE ; 
 TYPE_1__* pb_edit ; 
 int /*<<< orphan*/  speak_char (size_t) ; 
 short* spk_chartab ; 
 int /*<<< orphan*/  spk_msg_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * spk_special_handler ; 
 int /*<<< orphan*/  synth_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int edit_bits(struct vc_data *vc, u_char type, u_char ch, u_short key)
{
	short mask = pb_edit->mask, ch_type = spk_chartab[ch];

	if (type != KT_LATIN || (ch_type & B_NUM) || ch < SPACE)
		return -1;
	if (ch == SPACE) {
		synth_printf("%s\n", spk_msg_get(MSG_EDIT_DONE));
		spk_special_handler = NULL;
		return 1;
	}
	if (mask < PUNC && !(ch_type & PUNC))
		return -1;
	spk_chartab[ch] ^= mask;
	speak_char(ch);
	synth_printf(" %s\n",
		     (spk_chartab[ch] & mask) ? spk_msg_get(MSG_ON) :
		     spk_msg_get(MSG_OFF));
	return 1;
}