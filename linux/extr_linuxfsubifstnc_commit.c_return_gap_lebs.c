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
struct ubifs_info {int* gap_lebs; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPROPS_NC ; 
 int /*<<< orphan*/  LPROPS_TAKEN ; 
 int /*<<< orphan*/  dbg_cmt (char*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int ubifs_change_one_lp (struct ubifs_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int return_gap_lebs(struct ubifs_info *c)
{
	int *p, err;

	if (!c->gap_lebs)
		return 0;

	dbg_cmt("");
	for (p = c->gap_lebs; *p != -1; p++) {
		err = ubifs_change_one_lp(c, *p, LPROPS_NC, LPROPS_NC, 0,
					  LPROPS_TAKEN, 0);
		if (err)
			return err;
	}

	kfree(c->gap_lebs);
	c->gap_lebs = NULL;
	return 0;
}