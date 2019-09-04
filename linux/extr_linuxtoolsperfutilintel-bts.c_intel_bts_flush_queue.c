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
typedef  int /*<<< orphan*/  u64 ;
struct intel_bts_queue {int dummy; } ;

/* Variables and functions */
 int intel_bts_process_queue (struct intel_bts_queue*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_bts_flush_queue(struct intel_bts_queue *btsq)
{
	u64 ts = 0;
	int ret;

	while (1) {
		ret = intel_bts_process_queue(btsq, &ts);
		if (ret < 0)
			return ret;
		if (ret)
			break;
	}
	return 0;
}