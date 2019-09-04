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
typedef  int uint8_t ;
struct TYPE_2__ {int* buf_ptr; int /*<<< orphan*/  line_num; } ;

/* Variables and functions */
 int CH_EOF ; 
 int /*<<< orphan*/  PEEKC_EOB (int,int*) ; 
 TYPE_1__* file ; 
 int handle_eob () ; 
 int /*<<< orphan*/  tcc_error (char*) ; 

uint8_t *parse_comment(uint8_t *p)
{
	int c;

	p++;
	for (;;) {
		/* fast skip loop */
		for (;;) {
			c = *p;
			if (c == '\n' || c == '*' || c == '\\') {
				break;
			}
			p++;
			c = *p;
			if (c == '\n' || c == '*' || c == '\\') {
				break;
			}
			p++;
		}
		/* now we can handle all the cases */
		if (c == '\n') {
			file->line_num++;
			p++;
		} else if (c == '*') {
			p++;
			for (;;) {
				c = *p;
				if (c == '*') {
					p++;
				} else if (c == '/') {
					goto end_of_comment;
				} else if (c == '\\') {
					file->buf_ptr = p;
					c = handle_eob ();
					p = file->buf_ptr;
					if (c == '\\') {
						/* skip '\[\r]\n', otherwise just skip the stray */
						while (c == '\\') {
							PEEKC_EOB (c, p);
							if (c == '\n') {
								file->line_num++;
								PEEKC_EOB (c, p);
							} else if (c == '\r') {
								PEEKC_EOB (c, p);
								if (c == '\n') {
									file->line_num++;
									PEEKC_EOB (c, p);
								}
							} else {
								goto after_star;
							}
						}
					}
				} else {
					break;
				}
			}
after_star:
			;
		} else {
			/* stray, eob or eof */
			file->buf_ptr = p;
			c = handle_eob ();
			p = file->buf_ptr;
			if (c == CH_EOF) {
				tcc_error ("unexpected end of file in comment");
			} else if (c == '\\') {
				p++;
			}
		}
	}
end_of_comment:
	p++;
	return p;
}