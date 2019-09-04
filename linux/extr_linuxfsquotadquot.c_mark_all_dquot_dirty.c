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
struct dquot {int dummy; } ;

/* Variables and functions */
 int MAXQUOTAS ; 
 int mark_dquot_dirty (struct dquot* const) ; 

__attribute__((used)) static inline int mark_all_dquot_dirty(struct dquot * const *dquot)
{
	int ret, err, cnt;

	ret = err = 0;
	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (dquot[cnt])
			/* Even in case of error we have to continue */
			ret = mark_dquot_dirty(dquot[cnt]);
		if (!err)
			err = ret;
	}
	return err;
}