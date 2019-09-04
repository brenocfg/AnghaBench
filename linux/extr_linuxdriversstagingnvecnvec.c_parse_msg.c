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
struct nvec_msg {int* data; } ;
struct nvec_chip {int /*<<< orphan*/  notifier_list; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int EINVAL ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int*) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int*,int,int) ; 

__attribute__((used)) static int parse_msg(struct nvec_chip *nvec, struct nvec_msg *msg)
{
	if ((msg->data[0] & 1 << 7) == 0 && msg->data[3]) {
		dev_err(nvec->dev, "ec responded %*ph\n", 4, msg->data);
		return -EINVAL;
	}

	if ((msg->data[0] >> 7) == 1 && (msg->data[0] & 0x0f) == 5)
		print_hex_dump(KERN_WARNING, "ec system event ",
			       DUMP_PREFIX_NONE, 16, 1, msg->data,
			       msg->data[1] + 2, true);

	atomic_notifier_call_chain(&nvec->notifier_list, msg->data[0] & 0x8f,
				   msg->data);

	return 0;
}