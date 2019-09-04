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
struct vc_data {int vc_size_row; scalar_t__ vc_rows; scalar_t__ vc_cols; } ;
struct tty_struct {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct vc_data* d; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ atedge (int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 size_t fg_console ; 
 scalar_t__ ishardspace (char) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int limit (int,scalar_t__) ; 
 char* sel_buffer ; 
 int sel_buffer_lth ; 
 int sel_end ; 
 char sel_pos (int) ; 
 int sel_start ; 
 int /*<<< orphan*/  speakup_clear_selection () ; 
 struct vc_data* spk_sel_cons ; 
 int spk_xe ; 
 int spk_xs ; 
 int spk_ye ; 
 int spk_ys ; 
 int /*<<< orphan*/  swap (int,int) ; 
 TYPE_1__* vc_cons ; 

int speakup_set_selection(struct tty_struct *tty)
{
	int new_sel_start, new_sel_end;
	char *bp, *obp;
	int i, ps, pe;
	struct vc_data *vc = vc_cons[fg_console].d;

	spk_xs = limit(spk_xs, vc->vc_cols - 1);
	spk_ys = limit(spk_ys, vc->vc_rows - 1);
	spk_xe = limit(spk_xe, vc->vc_cols - 1);
	spk_ye = limit(spk_ye, vc->vc_rows - 1);
	ps = spk_ys * vc->vc_size_row + (spk_xs << 1);
	pe = spk_ye * vc->vc_size_row + (spk_xe << 1);

	if (ps > pe)	/* make sel_start <= sel_end */
		swap(ps, pe);

	if (spk_sel_cons != vc_cons[fg_console].d) {
		speakup_clear_selection();
		spk_sel_cons = vc_cons[fg_console].d;
		dev_warn(tty->dev,
			 "Selection: mark console not the same as cut\n");
		return -EINVAL;
	}

	new_sel_start = ps;
	new_sel_end = pe;

	/* select to end of line if on trailing space */
	if (new_sel_end > new_sel_start &&
	    !atedge(new_sel_end, vc->vc_size_row) &&
	    ishardspace(sel_pos(new_sel_end))) {
		for (pe = new_sel_end + 2; ; pe += 2)
			if (!ishardspace(sel_pos(pe)) ||
			    atedge(pe, vc->vc_size_row))
				break;
		if (ishardspace(sel_pos(pe)))
			new_sel_end = pe;
	}
	if ((new_sel_start == sel_start) && (new_sel_end == sel_end))
		return 0; /* no action required */

	sel_start = new_sel_start;
	sel_end = new_sel_end;
	/* Allocate a new buffer before freeing the old one ... */
	bp = kmalloc((sel_end - sel_start) / 2 + 1, GFP_ATOMIC);
	if (!bp) {
		speakup_clear_selection();
		return -ENOMEM;
	}
	kfree(sel_buffer);
	sel_buffer = bp;

	obp = bp;
	for (i = sel_start; i <= sel_end; i += 2) {
		*bp = sel_pos(i);
		if (!ishardspace(*bp++))
			obp = bp;
		if (!((i + 2) % vc->vc_size_row)) {
			/* strip trailing blanks from line and add newline,
			 * unless non-space at end of line.
			 */
			if (obp != bp) {
				bp = obp;
				*bp++ = '\r';
			}
			obp = bp;
		}
	}
	sel_buffer_lth = bp - sel_buffer;
	return 0;
}