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
struct lexer {char const* pos; char const* start; int /*<<< orphan*/  ring_buffer; int /*<<< orphan*/  end; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  lex_text ; 
 int /*<<< orphan*/  lexeme_ring_buffer_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rawmemchr (char const*,char) ; 

__attribute__((used)) static void lex_init(struct lexer *lexer, const char *input)
{
    lexer->state = lex_text;
    lexer->pos = lexer->start = input;
    lexer->end = rawmemchr(input, '\0');
    lexeme_ring_buffer_init(&lexer->ring_buffer);
}