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
struct TYPE_3__ {int /*<<< orphan*/  bufstart; scalar_t__ is_tsquery; } ;
typedef  TYPE_1__* TSVectorParseState ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
prssyntaxerror(TSVectorParseState state)
{
	ereport(ERROR,
			(errcode(ERRCODE_SYNTAX_ERROR),
			 state->is_tsquery ?
			 errmsg("syntax error in tsquery: \"%s\"", state->bufstart) :
			 errmsg("syntax error in tsvector: \"%s\"", state->bufstart)));
}