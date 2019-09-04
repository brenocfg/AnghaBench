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
struct cf_parser {TYPE_1__* cur_token; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CFTOKEN_NEWLINE ; 
 scalar_t__ CFTOKEN_NONE ; 
 scalar_t__ CFTOKEN_SPACETAB ; 

__attribute__((used)) static inline bool cf_next_token(struct cf_parser *p)
{
	if (p->cur_token->type != CFTOKEN_SPACETAB &&
	    p->cur_token->type != CFTOKEN_NEWLINE &&
	    p->cur_token->type != CFTOKEN_NONE)
		p->cur_token++;

	while (p->cur_token->type == CFTOKEN_SPACETAB ||
	       p->cur_token->type == CFTOKEN_NEWLINE)
		p->cur_token++;

	return p->cur_token->type != CFTOKEN_NONE;
}