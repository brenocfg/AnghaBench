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
struct lexeme {int dummy; } ;
struct stacked_lexeme {int /*<<< orphan*/  stack; struct lexeme lexeme; } ;
struct parser {int /*<<< orphan*/  stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwan_status_critical_perror (char*) ; 
 struct stacked_lexeme* malloc (int) ; 

__attribute__((used)) static void parser_push_lexeme(struct parser *parser, struct lexeme *lexeme)
{
    struct stacked_lexeme *stacked_lexeme = malloc(sizeof(*stacked_lexeme));
    if (!stacked_lexeme)
        lwan_status_critical_perror("Could not push parser lexeme");

    stacked_lexeme->lexeme = *lexeme;
    list_add(&parser->stack, &stacked_lexeme->stack);
}