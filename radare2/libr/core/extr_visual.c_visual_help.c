#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* print; int /*<<< orphan*/  panels_root; } ;
struct TYPE_6__ {int /*<<< orphan*/  cur_enabled; } ;
typedef  int /*<<< orphan*/  RStrBuf ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  help_msg_visual ; 
 int /*<<< orphan*/  help_msg_visual_fn ; 
 int /*<<< orphan*/  help_visual ; 
 int /*<<< orphan*/  r_cons_clear00 () ; 
 int /*<<< orphan*/  r_cons_flush () ; 
 int r_cons_less_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_cons_printf (char*,int /*<<< orphan*/ ) ; 
 int r_cons_readchar () ; 
 int /*<<< orphan*/  r_core_visual_append_help (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_visual_panels_root (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_appendf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_strbuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_strbuf_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_strbuf_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setcursor (TYPE_2__*,int) ; 

__attribute__((used)) static int visual_help(RCore *core) {
	int ret = 0;
	RStrBuf *p, *q;
repeat:
	p = r_strbuf_new (NULL);
	q = r_strbuf_new (NULL);
	if (!p) {
		return 0;
	}
	r_cons_clear00 ();
	r_core_visual_append_help (q, "Visual Help", help_visual);
	r_cons_printf ("%s", r_strbuf_get (q));
	r_cons_flush ();
	switch (r_cons_readchar ()) {
	case 'q':
		r_strbuf_free (p);
		return ret;
	case '!':
		r_core_visual_panels_root (core, core->panels_root);
		break;
	case '?':
		r_core_visual_append_help (p, "Visual mode help", help_msg_visual);
		r_core_visual_append_help (p, "Function Keys: (See 'e key.'), defaults to", help_msg_visual_fn);
		ret = r_cons_less_str (r_strbuf_get (p), "?");
		break;
	case 'v':
		r_strbuf_appendf (p, "Visual Views:\n\n");
		r_strbuf_appendf (p,
			" \\     toggle horizonal split mode\n"
			" tt     create a new tab (same as t+)\n"
			" t=     give a name to the current tab\n"
			" t-     close current tab\n"
			" th     select previous tab (same as tj)\n"
			" tl     select next tab (same as tk)\n"
			" t[1-9] select nth tab\n"
			" C   -> rotate scr.color=0,1,2,3\n"
			" R   -> rotate color theme with ecr command which honors scr.randpal\n"
		);
		ret = r_cons_less_str (r_strbuf_get (p), "?");
		break;
	case 'p':
		r_strbuf_appendf (p, "Visual Print Modes:\n\n");
		r_strbuf_appendf (p,
			" pP  -> change to the next/previous print mode (hex, dis, ..)\n"
			" TAB -> rotate between all the configurations for the current print mode\n"
		);
		ret = r_cons_less_str (r_strbuf_get (p), "?");
		break;
	case 'e':
		r_strbuf_appendf (p, "Visual Evals:\n\n");
		r_strbuf_appendf (p,
			" E      toggle asm.leahints\n"
			" &      rotate asm.bits=16,32,64\n"
		);
		ret = r_cons_less_str (r_strbuf_get (p), "?");
		break;
	case 'c':
		setcursor (core, !core->print->cur_enabled);
		r_strbuf_free (p);
		return ret;
	case 'i':
		r_strbuf_appendf (p, "Visual Insertion Help:\n\n");
		r_strbuf_appendf (p,
			" i   -> insert bits, bytes or text depending on view\n"
			" a   -> assemble instruction and write the bytes in the current offset\n"
			" A   -> visual assembler\n"
			" +   -> increment value of byte\n"
			" -   -> decrement value of byte\n"
		);
		ret = r_cons_less_str (r_strbuf_get (p), "?");
		break;
	case 'd':
		r_strbuf_appendf (p, "Visual Debugger Help:\n\n");
		r_strbuf_appendf (p,
			" $   -> set the program counter (PC register)\n"
			" s   -> step in\n"
			" S   -> step over\n"
			" B   -> toggle breakpoint\n"
			" :dc -> continue\n"
		);
		ret = r_cons_less_str (r_strbuf_get (p), "?");
		break;
	case 'm':
		r_strbuf_appendf (p, "Visual Moving Around:\n\n");
		r_strbuf_appendf (p,
			" g        type flag/offset/register name to seek\n"
			" hl       seek to the next/previous byte\n"
			" jk       seek to the next row (core.offset += hex.cols)\n"
			" JK       seek one page down\n"
			" ^        seek to the beginning of the current map\n"
			" $        seek to the end of the current map\n"
			" c        toggle cursor mode (use hjkl to move and HJKL to select a range)\n"
			" mK/'K    mark/go to Key (any key)\n"
		);
		ret = r_cons_less_str (r_strbuf_get (p), "?");
		break;
	case 'a':
		r_strbuf_appendf (p, "Visual Analysis:\n\n");
		r_strbuf_appendf (p,
			" df -> define function\n"
			" du -> undefine function\n"
			" dc -> define as code\n"
			" dw -> define as dword (32bit)\n"
			" dw -> define as qword (64bit)\n"
			" dd -> define current block or selected bytes as data\n"
			" V  -> view graph (same as press the 'space' key)\n"
		);
		ret = r_cons_less_str (r_strbuf_get (p), "?");
		break;
	}
	r_strbuf_free (p);
	r_strbuf_free (q);
	goto repeat;
	return ret;
}