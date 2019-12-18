#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dquot_warn {scalar_t__ w_type; TYPE_1__* w_sb; int /*<<< orphan*/  w_dq_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_dev; } ;

/* Variables and functions */
 int MAXQUOTAS ; 
 scalar_t__ QUOTA_NL_NOWARN ; 
 int /*<<< orphan*/  print_warning (struct dquot_warn*) ; 
 int /*<<< orphan*/  quota_send_warning (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void flush_warnings(struct dquot_warn *warn)
{
	int i;

	for (i = 0; i < MAXQUOTAS; i++) {
		if (warn[i].w_type == QUOTA_NL_NOWARN)
			continue;
#ifdef CONFIG_PRINT_QUOTA_WARNING
		print_warning(&warn[i]);
#endif
		quota_send_warning(warn[i].w_dq_id,
				   warn[i].w_sb->s_dev, warn[i].w_type);
	}
}