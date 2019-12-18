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
typedef  int /*<<< orphan*/  RStrBuf ;
typedef  int /*<<< orphan*/  RParse ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  r_parse_parse (int /*<<< orphan*/ *,char*,char*) ; 
 char* r_strbuf_get (int /*<<< orphan*/ *) ; 
 size_t r_strbuf_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void parseHeap(RParse *p, RStrBuf *s) {
	char *op_buf_asm = r_strbuf_get (s);
	size_t len = r_strbuf_length (s);
	char *out = malloc (64 + (len * 2));
	if (out) {
		*out = 0;
		strcpy (out , op_buf_asm);
	// XXX we shouldn't pad here because we have t orefactor the RParse API to handle boundaries and chunks properly
		r_parse_parse (p, op_buf_asm, out);
		r_strbuf_set (s, out);
		free (out);
	}
}