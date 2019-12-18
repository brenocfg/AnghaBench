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
struct parser {int dummy; } ;
struct lexeme {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ LEXEME_RIGHT_META ; 
 void* parser_text ; 
 void* unexpected_lexeme (struct lexeme*) ; 

__attribute__((used)) static void *parser_right_meta(struct parser *parser __attribute__((unused)),
                               struct lexeme *lexeme)
{
    if (lexeme->type != LEXEME_RIGHT_META)
        return unexpected_lexeme(lexeme);
    return parser_text;
}