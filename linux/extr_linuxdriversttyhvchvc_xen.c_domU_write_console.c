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
typedef  int /*<<< orphan*/  uint32_t ;
struct xencons_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HYPERVISOR_sched_op (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCHEDOP_yield ; 
 int __write_console (struct xencons_info*,char const*,int) ; 
 scalar_t__ unlikely (int) ; 
 struct xencons_info* vtermno_to_xencons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int domU_write_console(uint32_t vtermno, const char *data, int len)
{
	int ret = len;
	struct xencons_info *cons = vtermno_to_xencons(vtermno);
	if (cons == NULL)
		return -EINVAL;

	/*
	 * Make sure the whole buffer is emitted, polling if
	 * necessary.  We don't ever want to rely on the hvc daemon
	 * because the most interesting console output is when the
	 * kernel is crippled.
	 */
	while (len) {
		int sent = __write_console(cons, data, len);
		
		data += sent;
		len -= sent;

		if (unlikely(len))
			HYPERVISOR_sched_op(SCHEDOP_yield, NULL);
	}

	return ret;
}