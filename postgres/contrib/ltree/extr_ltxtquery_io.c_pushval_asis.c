#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
typedef  int int32 ;
struct TYPE_4__ {char* curop; char* op; int lenop; int sumlen; } ;
typedef  TYPE_1__ QPRS_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  ltree_crc32_sz (char*,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  pushquery (TYPE_1__*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ repalloc (void*,int) ; 

__attribute__((used)) static void
pushval_asis(QPRS_STATE *state, int type, char *strval, int lenval, uint16 flag)
{
	if (lenval > 0xffff)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("word is too long")));

	pushquery(state, type, ltree_crc32_sz(strval, lenval),
			  state->curop - state->op, lenval, flag);

	while (state->curop - state->op + lenval + 1 >= state->lenop)
	{
		int32		tmp = state->curop - state->op;

		state->lenop *= 2;
		state->op = (char *) repalloc((void *) state->op, state->lenop);
		state->curop = state->op + tmp;
	}
	memcpy((void *) state->curop, (void *) strval, lenval);
	state->curop += lenval;
	*(state->curop) = '\0';
	state->curop++;
	state->sumlen += lenval + 1;
	return;
}