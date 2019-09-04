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
struct tree_balance {int /*<<< orphan*/ ** CFL; int /*<<< orphan*/ * lkey; int /*<<< orphan*/  tb_path; int /*<<< orphan*/ ** L; } ;
struct item_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ B_NR_ITEMS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_SIZE ; 
 int /*<<< orphan*/  PATH_H_PBUFFER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RFALSE (int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_balance_mark_internal_dirty (struct tree_balance*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  internal_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct item_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void replace_lkey(struct tree_balance *tb, int h, struct item_head *key)
{
	RFALSE(tb->L[h] == NULL || tb->CFL[h] == NULL,
	       "L[h](%p) and CFL[h](%p) must exist in replace_lkey",
	       tb->L[h], tb->CFL[h]);

	if (B_NR_ITEMS(PATH_H_PBUFFER(tb->tb_path, h)) == 0)
		return;

	memcpy(internal_key(tb->CFL[h], tb->lkey[h]), key, KEY_SIZE);

	do_balance_mark_internal_dirty(tb, tb->CFL[h], 0);
}