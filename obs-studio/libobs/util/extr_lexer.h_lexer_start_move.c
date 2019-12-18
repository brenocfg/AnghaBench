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
struct lexer {char* text; char* offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  lexer_free (struct lexer*) ; 

__attribute__((used)) static inline void lexer_start_move(struct lexer *lex, char *text)
{
	lexer_free(lex);
	lex->text = text;
	lex->offset = lex->text;
}