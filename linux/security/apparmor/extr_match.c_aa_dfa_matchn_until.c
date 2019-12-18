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
typedef  scalar_t__ u32 ;
typedef  unsigned int u16 ;
struct aa_dfa {scalar_t__* tables; } ;

/* Variables and functions */
 scalar_t__* ACCEPT_TABLE (struct aa_dfa*) ; 
 scalar_t__* BASE_TABLE (struct aa_dfa*) ; 
 unsigned int* CHECK_TABLE (struct aa_dfa*) ; 
 unsigned int* DEFAULT_TABLE (struct aa_dfa*) ; 
 size_t* EQUIV_TABLE (struct aa_dfa*) ; 
 unsigned int* NEXT_TABLE (struct aa_dfa*) ; 
 size_t YYTD_ID_EC ; 
 size_t base_idx (scalar_t__) ; 

unsigned int aa_dfa_matchn_until(struct aa_dfa *dfa, unsigned int start,
				 const char *str, int n, const char **retpos)
{
	u16 *def = DEFAULT_TABLE(dfa);
	u32 *base = BASE_TABLE(dfa);
	u16 *next = NEXT_TABLE(dfa);
	u16 *check = CHECK_TABLE(dfa);
	u32 *accept = ACCEPT_TABLE(dfa);
	unsigned int state = start, pos;

	*retpos = NULL;
	if (state == 0)
		return 0;

	/* current state is <state>, matching character *str */
	if (dfa->tables[YYTD_ID_EC]) {
		/* Equivalence class table defined */
		u8 *equiv = EQUIV_TABLE(dfa);
		/* default is direct to next state */
		for (; n; n--) {
			pos = base_idx(base[state]) + equiv[(u8) *str++];
			if (check[pos] == state)
				state = next[pos];
			else
				state = def[state];
			if (accept[state])
				break;
		}
	} else {
		/* default is direct to next state */
		for (; n; n--) {
			pos = base_idx(base[state]) + (u8) *str++;
			if (check[pos] == state)
				state = next[pos];
			else
				state = def[state];
			if (accept[state])
				break;
		}
	}

	*retpos = str;
	return state;
}