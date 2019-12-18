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
typedef  int /*<<< orphan*/  TokenAuxData ;

/* Variables and functions */
 int internal_yylex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  push_back_token (int,int /*<<< orphan*/ *) ; 

int
plpgsql_peek(void)
{
	int			tok1;
	TokenAuxData aux1;

	tok1 = internal_yylex(&aux1);
	push_back_token(tok1, &aux1);
	return tok1;
}