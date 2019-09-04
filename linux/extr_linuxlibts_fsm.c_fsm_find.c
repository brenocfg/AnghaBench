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
typedef  int /*<<< orphan*/  u8 ;
struct ts_state {unsigned int offset; } ;
struct ts_fsm_token {scalar_t__ recur; } ;
struct ts_fsm {unsigned int ntokens; struct ts_fsm_token* tokens; } ;
struct ts_config {unsigned int (* get_next_block ) (unsigned int,int /*<<< orphan*/  const**,struct ts_config*,struct ts_state*) ;} ;

/* Variables and functions */
#define  TS_FSM_ANY 132 
#define  TS_FSM_HEAD_IGNORE 131 
#define  TS_FSM_MULTI 130 
#define  TS_FSM_PERHAPS 129 
#define  TS_FSM_SINGLE 128 
 unsigned int UINT_MAX ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  match_token (struct ts_fsm_token*,int /*<<< orphan*/  const) ; 
 unsigned int stub1 (unsigned int,int /*<<< orphan*/  const**,struct ts_config*,struct ts_state*) ; 
 unsigned int stub2 (unsigned int,int /*<<< orphan*/  const**,struct ts_config*,struct ts_state*) ; 
 unsigned int stub3 (unsigned int,int /*<<< orphan*/  const**,struct ts_config*,struct ts_state*) ; 
 unsigned int stub4 (unsigned int,int /*<<< orphan*/  const**,struct ts_config*,struct ts_state*) ; 
 unsigned int stub5 (unsigned int,int /*<<< orphan*/  const**,struct ts_config*,struct ts_state*) ; 
 unsigned int stub6 (unsigned int,int /*<<< orphan*/  const**,struct ts_config*,struct ts_state*) ; 
 unsigned int stub7 (unsigned int,int /*<<< orphan*/  const**,struct ts_config*,struct ts_state*) ; 
 unsigned int stub8 (unsigned int,int /*<<< orphan*/  const**,struct ts_config*,struct ts_state*) ; 
 unsigned int stub9 (unsigned int,int /*<<< orphan*/  const**,struct ts_config*,struct ts_state*) ; 
 struct ts_fsm* ts_config_priv (struct ts_config*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int fsm_find(struct ts_config *conf, struct ts_state *state)
{
	struct ts_fsm *fsm = ts_config_priv(conf);
	struct ts_fsm_token *cur = NULL, *next;
	unsigned int match_start, block_idx = 0, tok_idx;
	unsigned block_len = 0, strict, consumed = state->offset;
	const u8 *data;

#define GET_NEXT_BLOCK()		\
({	consumed += block_idx;		\
	block_idx = 0;			\
	block_len = conf->get_next_block(consumed, &data, conf, state); })

#define TOKEN_MISMATCH()		\
	do {				\
		if (strict)		\
			goto no_match;	\
		block_idx++;		\
		goto startover;		\
	} while(0)

#define end_of_data() unlikely(block_idx >= block_len && !GET_NEXT_BLOCK())

	if (end_of_data())
		goto no_match;

	strict = fsm->tokens[0].recur != TS_FSM_HEAD_IGNORE;

startover:
	match_start = consumed + block_idx;

	for (tok_idx = 0; tok_idx < fsm->ntokens; tok_idx++) {
		cur = &fsm->tokens[tok_idx];

		if (likely(tok_idx < (fsm->ntokens - 1)))
			next = &fsm->tokens[tok_idx + 1];
		else
			next = NULL;

		switch (cur->recur) {
		case TS_FSM_SINGLE:
			if (end_of_data())
				goto no_match;

			if (!match_token(cur, data[block_idx]))
				TOKEN_MISMATCH();
			break;

		case TS_FSM_PERHAPS:
			if (end_of_data() ||
			    !match_token(cur, data[block_idx]))
				continue;
			break;

		case TS_FSM_MULTI:
			if (end_of_data())
				goto no_match;

			if (!match_token(cur, data[block_idx]))
				TOKEN_MISMATCH();

			block_idx++;
			/* fall through */

		case TS_FSM_ANY:
			if (next == NULL)
				goto found_match;

			if (end_of_data())
				continue;

			while (!match_token(next, data[block_idx])) {
				if (!match_token(cur, data[block_idx]))
					TOKEN_MISMATCH();
				block_idx++;
				if (end_of_data())
					goto no_match;
			}
			continue;

		/*
		 * Optimization: Prefer small local loop over jumping
		 * back and forth until garbage at head is munched.
		 */
		case TS_FSM_HEAD_IGNORE:
			if (end_of_data())
				continue;

			while (!match_token(next, data[block_idx])) {
				/*
				 * Special case, don't start over upon
				 * a mismatch, give the user the
				 * chance to specify the type of data
				 * allowed to be ignored.
				 */
				if (!match_token(cur, data[block_idx]))
					goto no_match;

				block_idx++;
				if (end_of_data())
					goto no_match;
			}

			match_start = consumed + block_idx;
			continue;
		}

		block_idx++;
	}

	if (end_of_data())
		goto found_match;

no_match:
	return UINT_MAX;

found_match:
	state->offset = consumed + block_idx;
	return match_start;
}