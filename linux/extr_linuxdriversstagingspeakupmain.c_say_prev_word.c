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
typedef  scalar_t__ u_short ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int u16 ;
struct vc_data {scalar_t__ vc_cols; } ;

/* Variables and functions */
 scalar_t__ IS_WDLM (int) ; 
 int SPACE ; 
 int /*<<< orphan*/  announce_edge (struct vc_data*,scalar_t__) ; 
 scalar_t__ edge_left ; 
 scalar_t__ edge_quiet ; 
 scalar_t__ edge_top ; 
 int get_char (struct vc_data*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  say_word (struct vc_data*) ; 
 int spk_parked ; 
 scalar_t__ spk_pos ; 
 scalar_t__ spk_x ; 
 scalar_t__ spk_y ; 

__attribute__((used)) static void say_prev_word(struct vc_data *vc)
{
	u_char temp;
	u16 ch;
	u_short edge_said = 0, last_state = 0, state = 0;

	spk_parked |= 0x01;

	if (spk_x == 0) {
		if (spk_y == 0) {
			announce_edge(vc, edge_top);
			return;
		}
		spk_y--;
		spk_x = vc->vc_cols;
		edge_said = edge_quiet;
	}
	while (1) {
		if (spk_x == 0) {
			if (spk_y == 0) {
				edge_said = edge_top;
				break;
			}
			if (edge_said != edge_quiet)
				edge_said = edge_left;
			if (state > 0)
				break;
			spk_y--;
			spk_x = vc->vc_cols - 1;
		} else {
			spk_x--;
		}
		spk_pos -= 2;
		ch = get_char(vc, (u_short *)spk_pos, &temp);
		if (ch == SPACE || ch == 0)
			state = 0;
		else if (ch < 0x100 && IS_WDLM(ch))
			state = 1;
		else
			state = 2;
		if (state < last_state) {
			spk_pos += 2;
			spk_x++;
			break;
		}
		last_state = state;
	}
	if (spk_x == 0 && edge_said == edge_quiet)
		edge_said = edge_left;
	if (edge_said > 0 && edge_said < edge_quiet)
		announce_edge(vc, edge_said);
	say_word(vc);
}