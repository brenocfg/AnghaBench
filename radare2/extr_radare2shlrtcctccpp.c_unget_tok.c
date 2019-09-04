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
struct TYPE_2__ {int /*<<< orphan*/ * tab; } ;

/* Variables and functions */
 int* macro_ptr ; 
 int tok ; 
 int tok_ext_size (int) ; 
 TYPE_1__ tokc ; 
 int unget_buffer_enabled ; 
 int* unget_saved_buffer ; 
 int* unget_saved_macro_ptr ; 

void unget_tok(int last_tok)
{
	int i, n;
	int *q;
	if (unget_buffer_enabled) {
		/* assert(macro_ptr == unget_saved_buffer + 1);
		   assert(*macro_ptr == 0);  */
	} else {
		unget_saved_macro_ptr = macro_ptr;
		unget_buffer_enabled = 1;
	}
	q = unget_saved_buffer;
	macro_ptr = q;
	*q++ = tok;
	n = tok_ext_size (tok) - 1;
	for (i = 0; i < n; i++) {
		*q++ = tokc.tab[i];
	}
	*q = 0;	/* end of token string */
	tok = last_tok;
}