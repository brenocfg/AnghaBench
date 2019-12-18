#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  line_num; } ;
struct TYPE_4__ {int /*<<< orphan*/  i; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOK_GET (scalar_t__*,scalar_t__**,TYPE_1__*) ; 
 scalar_t__ TOK_LINENUM ; 
 TYPE_2__* file ; 
 scalar_t__* macro_ptr ; 
 int /*<<< orphan*/  next_nomacro1 () ; 
 scalar_t__ tok ; 
 TYPE_1__ tokc ; 

__attribute__((used)) static void next_nomacro_spc(void)
{
	if (macro_ptr) {
redo:
		tok = *macro_ptr;
		if (tok) {
			TOK_GET (&tok, &macro_ptr, &tokc);
			if (tok == TOK_LINENUM) {
				file->line_num = tokc.i;
				goto redo;
			}
		}
	} else {
		next_nomacro1 ();
	}
}