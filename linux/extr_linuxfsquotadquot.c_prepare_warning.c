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
struct dquot_warn {int w_type; int /*<<< orphan*/  w_dq_id; int /*<<< orphan*/  w_sb; } ;
struct dquot {int /*<<< orphan*/  dq_id; int /*<<< orphan*/  dq_sb; } ;

/* Variables and functions */
 scalar_t__ warning_issued (struct dquot*,int) ; 

__attribute__((used)) static void prepare_warning(struct dquot_warn *warn, struct dquot *dquot,
			    int warntype)
{
	if (warning_issued(dquot, warntype))
		return;
	warn->w_type = warntype;
	warn->w_sb = dquot->dq_sb;
	warn->w_dq_id = dquot->dq_id;
}