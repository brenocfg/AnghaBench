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
struct cf_token {scalar_t__ type; } ;
struct cf_preprocessor {int ignore_state; } ;

/* Variables and functions */
 scalar_t__ CFTOKEN_NONE ; 
 int /*<<< orphan*/  cf_adderror_unexpected_endif_eof (struct cf_preprocessor*,struct cf_token*) ; 
 int /*<<< orphan*/  cf_preprocess_tokens (struct cf_preprocessor*,int,struct cf_token**) ; 
 int /*<<< orphan*/  next_token (struct cf_token**,int) ; 

__attribute__((used)) static inline bool cf_preprocess_subblock(struct cf_preprocessor *pp,
					  bool ignore,
					  struct cf_token **p_cur_token)
{
	bool eof;

	if (!next_token(p_cur_token, true))
		return false;

	if (!pp->ignore_state) {
		pp->ignore_state = ignore;
		cf_preprocess_tokens(pp, true, p_cur_token);
		pp->ignore_state = false;
	} else {
		cf_preprocess_tokens(pp, true, p_cur_token);
	}

	eof = ((*p_cur_token)->type == CFTOKEN_NONE);
	if (eof)
		cf_adderror_unexpected_endif_eof(pp, *p_cur_token);
	return !eof;
}