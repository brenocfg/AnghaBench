#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  leng; int /*<<< orphan*/  lloc; int /*<<< orphan*/  lval; } ;
typedef  TYPE_1__ TokenAuxData ;

/* Variables and functions */
 int /*<<< orphan*/  plpgsql_yyleng ; 
 int /*<<< orphan*/  plpgsql_yylloc ; 
 int /*<<< orphan*/  plpgsql_yylval ; 
 int /*<<< orphan*/  push_back_token (int,TYPE_1__*) ; 

void
plpgsql_push_back_token(int token)
{
	TokenAuxData auxdata;

	auxdata.lval = plpgsql_yylval;
	auxdata.lloc = plpgsql_yylloc;
	auxdata.leng = plpgsql_yyleng;
	push_back_token(token, &auxdata);
}