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
 int /*<<< orphan*/  get_tok_str (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next () ; 
 int /*<<< orphan*/  tcc_error (char*,int,int /*<<< orphan*/ ) ; 
 int tok ; 
 int /*<<< orphan*/  tokc ; 

void skip(int c)
{
	if (tok != c) {
		tcc_error ("'%c' expected (got \"%s\")", c, get_tok_str (tok, &tokc));
	}
	next ();
}