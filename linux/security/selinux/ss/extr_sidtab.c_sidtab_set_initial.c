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
typedef  int u32 ;
struct sidtab_isid_entry {int set; int /*<<< orphan*/  context; } ;
struct sidtab {struct sidtab_isid_entry* isids; } ;
struct context {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SECINITSID_NUM ; 
 int context_cpy (int /*<<< orphan*/ *,struct context*) ; 

int sidtab_set_initial(struct sidtab *s, u32 sid, struct context *context)
{
	struct sidtab_isid_entry *entry;
	int rc;

	if (sid == 0 || sid > SECINITSID_NUM)
		return -EINVAL;

	entry = &s->isids[sid - 1];

	rc = context_cpy(&entry->context, context);
	if (rc)
		return rc;

	entry->set = 1;
	return 0;
}