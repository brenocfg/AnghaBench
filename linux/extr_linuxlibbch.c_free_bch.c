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
struct bch_control {struct bch_control** poly_2t; struct bch_control* elp; struct bch_control* cache; struct bch_control* syn; struct bch_control* xi_tab; struct bch_control* ecc_buf2; struct bch_control* ecc_buf; struct bch_control* mod8_tab; struct bch_control* a_log_tab; struct bch_control* a_pow_tab; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct bch_control**) ; 
 int /*<<< orphan*/  kfree (struct bch_control*) ; 

void free_bch(struct bch_control *bch)
{
	unsigned int i;

	if (bch) {
		kfree(bch->a_pow_tab);
		kfree(bch->a_log_tab);
		kfree(bch->mod8_tab);
		kfree(bch->ecc_buf);
		kfree(bch->ecc_buf2);
		kfree(bch->xi_tab);
		kfree(bch->syn);
		kfree(bch->cache);
		kfree(bch->elp);

		for (i = 0; i < ARRAY_SIZE(bch->poly_2t); i++)
			kfree(bch->poly_2t[i]);

		kfree(bch);
	}
}