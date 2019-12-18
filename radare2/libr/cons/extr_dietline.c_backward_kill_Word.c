#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int index; int length; int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {TYPE_1__ buffer; int /*<<< orphan*/  clipboard; } ;

/* Variables and functions */
 TYPE_2__ I ; 
 int /*<<< orphan*/  MAJOR_BREAK ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ is_word_break_char (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_line_clipboard_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_str_ndup (int /*<<< orphan*/ *,int) ; 
 int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void backward_kill_Word() {
	int i, len;
	if (I.buffer.index > 0) {
		for (i = I.buffer.index; i > 0 && is_word_break_char (I.buffer.data[i], MAJOR_BREAK); i--) {
			/* Move the cursor index back until we hit a non-word-break-character */
		}
		for (; i > 0 && !is_word_break_char (I.buffer.data[i], MAJOR_BREAK); i--) {
			/* Move the cursor index back until we hit a word-break-character */
		}
		if (i > 0) {
			i++;
		} else if (i < 0) {
			i = 0;
		}
		if (I.buffer.index > I.buffer.length) {
			I.buffer.length = I.buffer.index;
		}
		len = I.buffer.index - i + 1;
		free (I.clipboard);
		I.clipboard = r_str_ndup (I.buffer.data + i, len);
		r_line_clipboard_push (I.clipboard);
		memmove (I.buffer.data + i, I.buffer.data + I.buffer.index,
				I.buffer.length - I.buffer.index + 1);
		I.buffer.length = strlen (I.buffer.data);
		I.buffer.index = i;
	}
}