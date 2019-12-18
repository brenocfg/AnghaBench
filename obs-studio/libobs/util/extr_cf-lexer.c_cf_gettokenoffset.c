#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  array; } ;
struct cf_token {TYPE_2__ unmerged_str; } ;
struct cf_preprocessor {TYPE_1__* lex; } ;
struct TYPE_3__ {int /*<<< orphan*/  base_lexer; } ;

/* Variables and functions */
 int /*<<< orphan*/  lexer_getstroffset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cf_gettokenoffset(struct cf_preprocessor *pp,
				     const struct cf_token *token,
				     uint32_t *row, uint32_t *col)
{
	lexer_getstroffset(&pp->lex->base_lexer, token->unmerged_str.array, row,
			   col);
}