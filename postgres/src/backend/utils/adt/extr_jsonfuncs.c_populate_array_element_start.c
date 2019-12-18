#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * element_scalar; TYPE_1__* lex; int /*<<< orphan*/  element_type; int /*<<< orphan*/  element_start; TYPE_2__* ctx; } ;
struct TYPE_5__ {int ndims; } ;
struct TYPE_4__ {int lex_level; int /*<<< orphan*/  token_type; int /*<<< orphan*/  token_start; } ;
typedef  TYPE_3__ PopulateArrayState ;

/* Variables and functions */

__attribute__((used)) static void
populate_array_element_start(void *_state, bool isnull)
{
	PopulateArrayState *state = (PopulateArrayState *) _state;
	int			ndim = state->lex->lex_level;

	if (state->ctx->ndims <= 0 || ndim == state->ctx->ndims)
	{
		/* remember current array element start */
		state->element_start = state->lex->token_start;
		state->element_type = state->lex->token_type;
		state->element_scalar = NULL;
	}
}