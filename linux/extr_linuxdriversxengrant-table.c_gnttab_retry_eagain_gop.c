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
typedef  scalar_t__ int16_t ;
struct TYPE_2__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ GNTST_bad_page ; 
 scalar_t__ GNTST_eagain ; 
 int /*<<< orphan*/  HYPERVISOR_grant_table_op (unsigned int,void*,int) ; 
 unsigned int MAX_DELAY ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
gnttab_retry_eagain_gop(unsigned int cmd, void *gop, int16_t *status,
						const char *func)
{
	unsigned delay = 1;

	do {
		BUG_ON(HYPERVISOR_grant_table_op(cmd, gop, 1));
		if (*status == GNTST_eagain)
			msleep(delay++);
	} while ((*status == GNTST_eagain) && (delay < MAX_DELAY));

	if (delay >= MAX_DELAY) {
		pr_err("%s: %s eagain grant\n", func, current->comm);
		*status = GNTST_bad_page;
	}
}