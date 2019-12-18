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
typedef  int /*<<< orphan*/  u16 ;
struct aa_dfa {scalar_t__* tables; } ;

/* Variables and functions */
 int /*<<< orphan*/ * BASE_TABLE (struct aa_dfa*) ; 
 int /*<<< orphan*/ * CHECK_TABLE (struct aa_dfa*) ; 
 int /*<<< orphan*/ * DEFAULT_TABLE (struct aa_dfa*) ; 
 size_t* EQUIV_TABLE (struct aa_dfa*) ; 
 int /*<<< orphan*/ * NEXT_TABLE (struct aa_dfa*) ; 
 size_t YYTD_ID_EC ; 
 int /*<<< orphan*/  match_char (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

unsigned int aa_dfa_match_len(struct aa_dfa *dfa, unsigned int start,
			      const char *str, int len)
{
	u16 *def = DEFAULT_TABLE(dfa);
	u32 *base = BASE_TABLE(dfa);
	u16 *next = NEXT_TABLE(dfa);
	u16 *check = CHECK_TABLE(dfa);
	unsigned int state = start;

	if (state == 0)
		return 0;

	/* current state is <state>, matching character *str */
	if (dfa->tables[YYTD_ID_EC]) {
		/* Equivalence class table defined */
		u8 *equiv = EQUIV_TABLE(dfa);
		for (; len; len--)
			match_char(state, def, base, next, check,
				   equiv[(u8) *str++]);
	} else {
		/* default is direct to next state */
		for (; len; len--)
			match_char(state, def, base, next, check, (u8) *str++);
	}

	return state;
}