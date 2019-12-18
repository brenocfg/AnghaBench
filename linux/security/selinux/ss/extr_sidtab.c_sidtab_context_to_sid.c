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
typedef  size_t u32 ;
struct sidtab_isid_entry {int /*<<< orphan*/  context; scalar_t__ set; } ;
struct sidtab {struct sidtab_isid_entry* isids; } ;
struct context {int dummy; } ;

/* Variables and functions */
 size_t SECINITSID_NUM ; 
 scalar_t__ context_cmp (struct context*,int /*<<< orphan*/ *) ; 
 int sidtab_reverse_lookup (struct sidtab*,struct context*,size_t*) ; 

int sidtab_context_to_sid(struct sidtab *s, struct context *context, u32 *sid)
{
	int rc;
	u32 i;

	for (i = 0; i < SECINITSID_NUM; i++) {
		struct sidtab_isid_entry *entry = &s->isids[i];

		if (entry->set && context_cmp(context, &entry->context)) {
			*sid = i + 1;
			return 0;
		}
	}

	rc = sidtab_reverse_lookup(s, context, sid);
	if (rc)
		return rc;
	*sid += SECINITSID_NUM + 1;
	return 0;
}