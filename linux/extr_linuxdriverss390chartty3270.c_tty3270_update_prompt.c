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
struct TYPE_2__ {int cols; int rows; int /*<<< orphan*/  dev; } ;
struct tty3270 {int /*<<< orphan*/  update_flags; TYPE_1__ view; scalar_t__ inattr; struct string* prompt; } ;
struct string {int len; scalar_t__* string; } ;

/* Variables and functions */
 scalar_t__ TF_INMDT ; 
 scalar_t__ TO_IC ; 
 scalar_t__ TO_RA ; 
 int /*<<< orphan*/  TTY_UPDATE_INPUT ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char*,int) ; 
 int /*<<< orphan*/  raw3270_buffer_address (int /*<<< orphan*/ ,scalar_t__*,unsigned int) ; 

__attribute__((used)) static void
tty3270_update_prompt(struct tty3270 *tp, char *input, int count)
{
	struct string *line;
	unsigned int off;

	line = tp->prompt;
	if (count != 0)
		line->string[5] = TF_INMDT;
	else
		line->string[5] = tp->inattr;
	if (count > tp->view.cols * 2 - 11)
		count = tp->view.cols * 2 - 11;
	memcpy(line->string + 6, input, count);
	line->string[6 + count] = TO_IC;
	/* Clear to end of input line. */
	if (count < tp->view.cols * 2 - 11) {
		line->string[7 + count] = TO_RA;
		line->string[10 + count] = 0;
		off = tp->view.cols * tp->view.rows - 9;
		raw3270_buffer_address(tp->view.dev, line->string+count+8, off);
		line->len = 11 + count;
	} else
		line->len = 7 + count;
	tp->update_flags |= TTY_UPDATE_INPUT;
}