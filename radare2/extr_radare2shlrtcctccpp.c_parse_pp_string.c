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
typedef  int /*<<< orphan*/  CString ;

/* Variables and functions */
 int CH_EOF ; 
 int /*<<< orphan*/  PEEKC_EOB (int,int*) ; 
 int /*<<< orphan*/  cstr_ccat (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  expect (char*) ; 
 TYPE_1__* file ; 
 int handle_eob () ; 
 int /*<<< orphan*/  tcc_error (char*,int) ; 
 scalar_t__ tcc_nerr () ; 

__attribute__((used)) static uint8_t *parse_pp_string(uint8_t *p,
				int sep, CString *str)
{
	int c;
	p++;
	while (tcc_nerr () == 0) {
		c = *p;
		if (c == sep) {
			break;
		} else if (c == '\\') {
			file->buf_ptr = p;
			c = handle_eob ();
			p = file->buf_ptr;
			if (c == CH_EOF) {
unterminated_string:
				/* XXX: indicate line number of start of string */
				tcc_error ("missing terminating %c character", sep);
				return NULL;
			} else if (c == '\\') {
				/* escape : just skip \[\r]\n */
				PEEKC_EOB (c, p);
				if (c == '\n') {
					file->line_num++;
					p++;
				} else if (c == '\r') {
					PEEKC_EOB (c, p);
					if (c != '\n') {
						expect ("'\n' after '\r'");
						return NULL;
					}
					file->line_num++;
					p++;
				} else if (c == CH_EOF) {
					goto unterminated_string;
				} else {
					if (str) {
						cstr_ccat (str, '\\');
						cstr_ccat (str, c);
					}
					p++;
				}
			}
		} else if (c == '\n') {
			file->line_num++;
			goto add_char;
		} else if (c == '\r') {
			PEEKC_EOB (c, p);
			if (c != '\n') {
				if (str) {
					cstr_ccat (str, '\r');
				}
			} else {
				file->line_num++;
				goto add_char;
			}
		} else {
add_char:
			if (str) {
				cstr_ccat (str, c);
			}
			p++;
		}
	}
	p++;
	return p;
}