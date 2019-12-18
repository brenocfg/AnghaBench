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
struct cf_lexer {int unexpected_eof; int /*<<< orphan*/ * write_offset; int /*<<< orphan*/ * reformatted; int /*<<< orphan*/ * file; int /*<<< orphan*/  tokens; int /*<<< orphan*/  base_lexer; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lexer_init (int /*<<< orphan*/ *) ; 

void cf_lexer_init(struct cf_lexer *lex)
{
	lexer_init(&lex->base_lexer);
	da_init(lex->tokens);

	lex->file = NULL;
	lex->reformatted = NULL;
	lex->write_offset = NULL;
	lex->unexpected_eof = false;
}