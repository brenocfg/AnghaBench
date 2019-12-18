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
struct TSVectorParseStateData {int dummy; } ;
struct TYPE_3__ {char* prsbuf; char* bufstart; int len; char* word; int oprisdelim; int is_tsquery; int is_web; int /*<<< orphan*/  eml; } ;
typedef  TYPE_1__* TSVectorParseState ;

/* Variables and functions */
 int P_TSV_IS_TSQUERY ; 
 int P_TSV_IS_WEB ; 
 int P_TSV_OPR_IS_DELIM ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pg_database_encoding_max_length () ; 

TSVectorParseState
init_tsvector_parser(char *input, int flags)
{
	TSVectorParseState state;

	state = (TSVectorParseState) palloc(sizeof(struct TSVectorParseStateData));
	state->prsbuf = input;
	state->bufstart = input;
	state->len = 32;
	state->word = (char *) palloc(state->len);
	state->eml = pg_database_encoding_max_length();
	state->oprisdelim = (flags & P_TSV_OPR_IS_DELIM) != 0;
	state->is_tsquery = (flags & P_TSV_IS_TSQUERY) != 0;
	state->is_web = (flags & P_TSV_IS_WEB) != 0;

	return state;
}