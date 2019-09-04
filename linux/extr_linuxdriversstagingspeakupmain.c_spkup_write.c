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
typedef  int u_short ;
typedef  int u16 ;

/* Variables and functions */
 int ALPHA ; 
 int B_ALPHA ; 
 int B_NUM ; 
 int CH_RPT ; 
 int MINECHOCHAR ; 
 int /*<<< orphan*/  MSG_REPEAT_DESC ; 
 int /*<<< orphan*/  MSG_REPEAT_DESC2 ; 
 int PUNC ; 
 int SF_DEC ; 
 int /*<<< orphan*/  SPACE ; 
 int SYNTH_OK ; 
 size_t bn ; 
 size_t currsentence ; 
 scalar_t__ cursor_track ; 
 size_t* numsentences ; 
 scalar_t__ read_all_mode ; 
 int const*** sentmarks ; 
 int /*<<< orphan*/  speak_char (int) ; 
 int* spk_chartab ; 
 int spk_key_echo ; 
 scalar_t__ spk_keydown ; 
 int spk_lastkey ; 
 int /*<<< orphan*/  spk_msg_get (int /*<<< orphan*/ ) ; 
 int spk_punc_mask ; 
 int /*<<< orphan*/  synth_buffer_add (int /*<<< orphan*/ ) ; 
 int synth_flags ; 
 int /*<<< orphan*/  synth_insert_next_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synth_printf (char*,...) ; 
 int /*<<< orphan*/  synth_putwc_s (int) ; 

__attribute__((used)) static void spkup_write(const u16 *in_buf, int count)
{
	static int rep_count;
	static u16 ch = '\0', old_ch = '\0';
	static u_short char_type, last_type;
	int in_count = count;

	spk_keydown = 0;
	while (count--) {
		if (cursor_track == read_all_mode) {
			/* Insert Sentence Index */
			if ((in_buf == sentmarks[bn][currsentence]) &&
			    (currsentence <= numsentences[bn]))
				synth_insert_next_index(currsentence++);
		}
		ch = *in_buf++;
		if (ch < 0x100)
			char_type = spk_chartab[ch];
		else
			char_type = ALPHA;
		if (ch == old_ch && !(char_type & B_NUM)) {
			if (++rep_count > 2)
				continue;
		} else {
			if ((last_type & CH_RPT) && rep_count > 2) {
				synth_printf(" ");
				synth_printf(spk_msg_get(MSG_REPEAT_DESC),
					     ++rep_count);
				synth_printf(" ");
			}
			rep_count = 0;
		}
		if (ch == spk_lastkey) {
			rep_count = 0;
			if (spk_key_echo == 1 && ch >= MINECHOCHAR)
				speak_char(ch);
		} else if (char_type & B_ALPHA) {
			if ((synth_flags & SF_DEC) && (last_type & PUNC))
				synth_buffer_add(SPACE);
			synth_putwc_s(ch);
		} else if (char_type & B_NUM) {
			rep_count = 0;
			synth_putwc_s(ch);
		} else if (char_type & spk_punc_mask) {
			speak_char(ch);
			char_type &= ~PUNC;	/* for dec nospell processing */
		} else if (char_type & SYNTH_OK) {
			/* these are usually puncts like . and , which synth
			 * needs for expression.
			 * suppress multiple to get rid of long pauses and
			 * clear repeat count
			 * so if someone has
			 * repeats on you don't get nothing repeated count
			 */
			if (ch != old_ch)
				synth_putwc_s(ch);
			else
				rep_count = 0;
		} else {
/* send space and record position, if next is num overwrite space */
			if (old_ch != ch)
				synth_buffer_add(SPACE);
			else
				rep_count = 0;
		}
		old_ch = ch;
		last_type = char_type;
	}
	spk_lastkey = 0;
	if (in_count > 2 && rep_count > 2) {
		if (last_type & CH_RPT) {
			synth_printf(" ");
			synth_printf(spk_msg_get(MSG_REPEAT_DESC2),
				     ++rep_count);
			synth_printf(" ");
		}
		rep_count = 0;
	}
}