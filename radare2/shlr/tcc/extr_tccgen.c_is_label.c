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

/* Variables and functions */
 char TOK_UIDENT ; 
 int /*<<< orphan*/  next () ; 
 char tok ; 
 int /*<<< orphan*/  unget_tok (int) ; 

__attribute__((used)) static int is_label(void) {
	int last_tok;

	/* fast test first */
	if (tok < TOK_UIDENT) {
		return 0;
	}
	/* no need to save tokc because tok is an identifier */
	last_tok = tok;
	next ();
	if (tok == ':') {
		next ();
		return last_tok;
	} else {
		unget_tok (last_tok);
		return 0;
	}
}