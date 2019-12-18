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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  unsigned int u16 ;
struct match_workbuf {unsigned int* history; size_t pos; } ;
struct aa_dfa {scalar_t__* tables; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/ * BASE_TABLE (struct aa_dfa*) ; 
 unsigned int* CHECK_TABLE (struct aa_dfa*) ; 
 unsigned int* DEFAULT_TABLE (struct aa_dfa*) ; 
 size_t* EQUIV_TABLE (struct aa_dfa*) ; 
 unsigned int* NEXT_TABLE (struct aa_dfa*) ; 
 size_t YYTD_ID_EC ; 
 unsigned int aa_dfa_match (struct aa_dfa*,unsigned int,char const*) ; 
 size_t base_idx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_wb_pos (struct match_workbuf*) ; 
 scalar_t__ is_loop (struct match_workbuf*,unsigned int,unsigned int*) ; 

__attribute__((used)) static unsigned int leftmatch_fb(struct aa_dfa *dfa, unsigned int start,
				 const char *str, struct match_workbuf *wb,
				 unsigned int *count)
{
	u16 *def = DEFAULT_TABLE(dfa);
	u32 *base = BASE_TABLE(dfa);
	u16 *next = NEXT_TABLE(dfa);
	u16 *check = CHECK_TABLE(dfa);
	unsigned int state = start, pos;

	AA_BUG(!dfa);
	AA_BUG(!str);
	AA_BUG(!wb);
	AA_BUG(!count);

	*count = 0;
	if (state == 0)
		return 0;

	/* current state is <state>, matching character *str */
	if (dfa->tables[YYTD_ID_EC]) {
		/* Equivalence class table defined */
		u8 *equiv = EQUIV_TABLE(dfa);
		/* default is direct to next state */
		while (*str) {
			unsigned int adjust;

			wb->history[wb->pos] = state;
			pos = base_idx(base[state]) + equiv[(u8) *str++];
			if (check[pos] == state)
				state = next[pos];
			else
				state = def[state];
			if (is_loop(wb, state, &adjust)) {
				state = aa_dfa_match(dfa, state, str);
				*count -= adjust;
				goto out;
			}
			inc_wb_pos(wb);
			(*count)++;
		}
	} else {
		/* default is direct to next state */
		while (*str) {
			unsigned int adjust;

			wb->history[wb->pos] = state;
			pos = base_idx(base[state]) + (u8) *str++;
			if (check[pos] == state)
				state = next[pos];
			else
				state = def[state];
			if (is_loop(wb, state, &adjust)) {
				state = aa_dfa_match(dfa, state, str);
				*count -= adjust;
				goto out;
			}
			inc_wb_pos(wb);
			(*count)++;
		}
	}

out:
	if (!state)
		*count = 0;
	return state;
}