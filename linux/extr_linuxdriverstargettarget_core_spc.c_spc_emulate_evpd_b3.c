#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lba_map_segment_multiplier; int /*<<< orphan*/  lba_map_segment_size; } ;
struct se_device {TYPE_2__ t10_alua; TYPE_1__* transport; } ;
struct se_cmd {struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
struct TYPE_3__ {unsigned char (* get_device_type ) (struct se_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  put_unaligned_be32 (int /*<<< orphan*/ ,unsigned char*) ; 
 unsigned char stub1 (struct se_device*) ; 

__attribute__((used)) static sense_reason_t
spc_emulate_evpd_b3(struct se_cmd *cmd, unsigned char *buf)
{
	struct se_device *dev = cmd->se_dev;

	buf[0] = dev->transport->get_device_type(dev);
	buf[3] = 0x0c;
	put_unaligned_be32(dev->t10_alua.lba_map_segment_size, &buf[8]);
	put_unaligned_be32(dev->t10_alua.lba_map_segment_multiplier, &buf[12]);

	return 0;
}