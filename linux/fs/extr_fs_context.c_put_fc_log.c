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
struct fs_context {struct fc_log* log; } ;
struct fc_log {int need_free; struct fc_log** buffer; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct fc_log*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_fc_log(struct fs_context *fc)
{
	struct fc_log *log = fc->log;
	int i;

	if (log) {
		if (refcount_dec_and_test(&log->usage)) {
			fc->log = NULL;
			for (i = 0; i <= 7; i++)
				if (log->need_free & (1 << i))
					kfree(log->buffer[i]);
			kfree(log);
		}
	}
}