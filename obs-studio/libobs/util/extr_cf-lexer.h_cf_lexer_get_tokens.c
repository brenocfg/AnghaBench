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
struct cf_token {int dummy; } ;
struct TYPE_2__ {struct cf_token* array; } ;
struct cf_lexer {TYPE_1__ tokens; } ;

/* Variables and functions */

__attribute__((used)) static inline struct cf_token *cf_lexer_get_tokens(struct cf_lexer *lex)
{
	return lex->tokens.array;
}