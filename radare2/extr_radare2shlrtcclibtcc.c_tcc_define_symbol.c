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
struct TYPE_2__ {char* buffer; int /*<<< orphan*/ * buf_ptr; } ;
typedef  int /*<<< orphan*/  TCCState ;

/* Variables and functions */
 int /*<<< orphan*/  ch ; 
 TYPE_1__* file ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  next_nomacro () ; 
 int /*<<< orphan*/  parse_define () ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  tcc_close () ; 
 int /*<<< orphan*/  tcc_open_bf (int /*<<< orphan*/ *,char*,int) ; 

void tcc_define_symbol(TCCState *s1, const char *sym, const char *value)
{
	int len1, len2;
	/* default value */
	if (!value) {
		value = "1";
	}
	len1 = strlen (sym);
	len2 = strlen (value);

	/* init file structure */
	tcc_open_bf (s1, "<define>", len1 + len2 + 1);
	memcpy (file->buffer, sym, len1);
	file->buffer[len1] = ' ';
	memcpy (file->buffer + len1 + 1, value, len2);

	/* parse with define parser */
	ch = file->buf_ptr[0];
	next_nomacro ();
	parse_define ();

	tcc_close ();
}