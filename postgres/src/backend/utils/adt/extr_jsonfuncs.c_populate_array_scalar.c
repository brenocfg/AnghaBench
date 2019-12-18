#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int ndims; } ;
struct TYPE_7__ {char* element_scalar; scalar_t__ element_type; TYPE_1__* lex; TYPE_3__* ctx; } ;
struct TYPE_6__ {int lex_level; } ;
typedef  TYPE_2__ PopulateArrayState ;
typedef  TYPE_3__ PopulateArrayContext ;
typedef  scalar_t__ JsonTokenType ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  populate_array_assign_ndims (TYPE_3__*,int) ; 
 int /*<<< orphan*/  populate_array_report_expected_array (TYPE_3__*,int) ; 

__attribute__((used)) static void
populate_array_scalar(void *_state, char *token, JsonTokenType tokentype)
{
	PopulateArrayState *state = (PopulateArrayState *) _state;
	PopulateArrayContext *ctx = state->ctx;
	int			ndim = state->lex->lex_level;

	if (ctx->ndims <= 0)
		populate_array_assign_ndims(ctx, ndim);
	else if (ndim < ctx->ndims)
		populate_array_report_expected_array(ctx, ndim);

	if (ndim == ctx->ndims)
	{
		/* remember the scalar element token */
		state->element_scalar = token;
		/* element_type must already be set in populate_array_element_start() */
		Assert(state->element_type == tokentype);
	}
}