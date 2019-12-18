#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int index; int length; scalar_t__ data; } ;
struct TYPE_9__ {char* prompt; TYPE_2__ buffer; } ;
struct TYPE_8__ {int /*<<< orphan*/  rows; TYPE_1__* line; } ;
struct TYPE_6__ {scalar_t__ prompt_type; } ;
typedef  TYPE_3__ RCons ;

/* Variables and functions */
 char* Color_RESET ; 
 TYPE_5__ I ; 
 scalar_t__ R_LINE_PROMPT_OFFSET ; 
 int R_MAX (int,int) ; 
 int R_MIN (int,int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  r_cons_clear_line (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_cons_flush () ; 
 int r_cons_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_gotoxy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* r_cons_singleton () ; 
 int r_str_ansi_len (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (scalar_t__) ; 

__attribute__((used)) static void __print_prompt() {
        RCons *cons = r_cons_singleton ();
	int columns = r_cons_get_size (NULL) - 2;
	int chars = R_MAX (1, strlen (I.buffer.data));	
	int len, i, cols = R_MAX (1, columns - r_str_ansi_len (I.prompt) - 2);
	if (cons->line->prompt_type == R_LINE_PROMPT_OFFSET) {
                r_cons_gotoxy (0,  cons->rows);
                r_cons_flush ();
	}
	r_cons_clear_line (0);
	printf ("\r%s%s", Color_RESET, I.prompt);
	fwrite (I.buffer.data, 1, R_MIN (cols, chars), stdout);
	printf ("\r%s", I.prompt);
	if (I.buffer.index > cols) {
		printf ("< ");
		i = I.buffer.index - cols;
		if (i > sizeof (I.buffer.data)) {
			i = sizeof (I.buffer.data) - 1;
		}
	} else {
		i = 0;
	}
	len = I.buffer.index - i;
	if (len > 0 && (i + len) <= I.buffer.length) {
		fwrite (I.buffer.data + i, 1, len, stdout);
	}
	fflush (stdout);
}