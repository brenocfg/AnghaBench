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
typedef  int /*<<< orphan*/  ts_tokentype ;
typedef  int /*<<< orphan*/  int8 ;
typedef  scalar_t__ int16 ;
struct TYPE_3__ {char* buf; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__* TSQueryParserState ;

/* Variables and functions */
 int /*<<< orphan*/  PT_END ; 
 int /*<<< orphan*/  PT_VAL ; 
 int strlen (char*) ; 

__attribute__((used)) static ts_tokentype
gettoken_query_plain(TSQueryParserState state, int8 *operator,
					 int *lenval, char **strval,
					 int16 *weight, bool *prefix)
{
	*weight = 0;
	*prefix = false;

	if (*state->buf == '\0')
		return PT_END;

	*strval = state->buf;
	*lenval = strlen(state->buf);
	state->buf += *lenval;
	state->count++;
	return PT_VAL;
}