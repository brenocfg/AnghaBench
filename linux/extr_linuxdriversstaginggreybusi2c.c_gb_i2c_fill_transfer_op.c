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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_msg {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; int /*<<< orphan*/  flags; } ;
struct gb_i2c_transfer_op {void* size; void* flags; void* addr; } ;

/* Variables and functions */
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_i2c_transfer_op_flags_map (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gb_i2c_fill_transfer_op(struct gb_i2c_transfer_op *op, struct i2c_msg *msg)
{
	u16 flags = gb_i2c_transfer_op_flags_map(msg->flags);

	op->addr = cpu_to_le16(msg->addr);
	op->flags = cpu_to_le16(flags);
	op->size = cpu_to_le16(msg->len);
}