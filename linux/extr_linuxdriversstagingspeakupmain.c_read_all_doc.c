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
struct vc_data {scalar_t__ vc_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  RA_DOWN_ARROW ; 
 int /*<<< orphan*/  RA_TIMER ; 
 int /*<<< orphan*/  cursor_timer ; 
 scalar_t__ cursor_track ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ fg_console ; 
 int get_sentence_buf (struct vc_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_keyboard_notifier ; 
 scalar_t__ prev_cursor_track ; 
 scalar_t__ read_all_mode ; 
 int /*<<< orphan*/  say_sentence_num (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  speakup_fake_down_arrow () ; 
 int /*<<< orphan*/  spk_reset_index_count (int /*<<< orphan*/ ) ; 
 scalar_t__ spk_shut_up ; 
 int /*<<< orphan*/  start_read_all_timer (struct vc_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synth ; 
 int /*<<< orphan*/  synth_insert_next_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synth_supports_indexing () ; 

__attribute__((used)) static void read_all_doc(struct vc_data *vc)
{
	if ((vc->vc_num != fg_console) || !synth || spk_shut_up)
		return;
	if (!synth_supports_indexing())
		return;
	if (cursor_track != read_all_mode)
		prev_cursor_track = cursor_track;
	cursor_track = read_all_mode;
	spk_reset_index_count(0);
	if (get_sentence_buf(vc, 0) == -1) {
		del_timer(&cursor_timer);
		if (!in_keyboard_notifier)
			speakup_fake_down_arrow();
		start_read_all_timer(vc, RA_DOWN_ARROW);
	} else {
		say_sentence_num(0, 0);
		synth_insert_next_index(0);
		start_read_all_timer(vc, RA_TIMER);
	}
}