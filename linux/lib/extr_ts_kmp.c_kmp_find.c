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
typedef  scalar_t__ u8 ;
struct ts_state {unsigned int offset; } ;
struct ts_kmp {scalar_t__ const* pattern; unsigned int* prefix_tbl; unsigned int pattern_len; } ;
struct ts_config {int flags; unsigned int (* get_next_block ) (unsigned int,scalar_t__ const**,struct ts_config*,struct ts_state*) ;} ;

/* Variables and functions */
 int TS_IGNORECASE ; 
 unsigned int UINT_MAX ; 
 unsigned int stub1 (unsigned int,scalar_t__ const**,struct ts_config*,struct ts_state*) ; 
 scalar_t__ const toupper (scalar_t__ const) ; 
 struct ts_kmp* ts_config_priv (struct ts_config*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int kmp_find(struct ts_config *conf, struct ts_state *state)
{
	struct ts_kmp *kmp = ts_config_priv(conf);
	unsigned int i, q = 0, text_len, consumed = state->offset;
	const u8 *text;
	const int icase = conf->flags & TS_IGNORECASE;

	for (;;) {
		text_len = conf->get_next_block(consumed, &text, conf, state);

		if (unlikely(text_len == 0))
			break;

		for (i = 0; i < text_len; i++) {
			while (q > 0 && kmp->pattern[q]
			    != (icase ? toupper(text[i]) : text[i]))
				q = kmp->prefix_tbl[q - 1];
			if (kmp->pattern[q]
			    == (icase ? toupper(text[i]) : text[i]))
				q++;
			if (unlikely(q == kmp->pattern_len)) {
				state->offset = consumed + i + 1;
				return state->offset - kmp->pattern_len;
			}
		}

		consumed += text_len;
	}

	return UINT_MAX;
}