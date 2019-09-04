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
struct vc_data {int vc_size_row; scalar_t__ vc_origin; } ;
struct display {int dummy; } ;

/* Variables and functions */
 unsigned short* advance_row (unsigned short*,int) ; 
 int /*<<< orphan*/  console_conditional_schedule () ; 
 int /*<<< orphan*/  fbcon_putcs (struct vc_data*,unsigned short*,int,int,int) ; 
 unsigned short scr_readw (unsigned short*) ; 

__attribute__((used)) static void fbcon_redraw_move(struct vc_data *vc, struct display *p,
			      int line, int count, int dy)
{
	unsigned short *s = (unsigned short *)
		(vc->vc_origin + vc->vc_size_row * line);

	while (count--) {
		unsigned short *start = s;
		unsigned short *le = advance_row(s, 1);
		unsigned short c;
		int x = 0;
		unsigned short attr = 1;

		do {
			c = scr_readw(s);
			if (attr != (c & 0xff00)) {
				attr = c & 0xff00;
				if (s > start) {
					fbcon_putcs(vc, start, s - start,
						    dy, x);
					x += s - start;
					start = s;
				}
			}
			console_conditional_schedule();
			s++;
		} while (s < le);
		if (s > start)
			fbcon_putcs(vc, start, s - start, dy, x);
		console_conditional_schedule();
		dy++;
	}
}