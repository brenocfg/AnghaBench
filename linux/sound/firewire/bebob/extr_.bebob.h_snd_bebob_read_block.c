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
typedef  scalar_t__ u64 ;
struct fw_unit {int dummy; } ;

/* Variables and functions */
 scalar_t__ BEBOB_ADDR_REG_INFO ; 
 int /*<<< orphan*/  TCODE_READ_BLOCK_REQUEST ; 
 int snd_fw_transaction (struct fw_unit*,int /*<<< orphan*/ ,scalar_t__,void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
snd_bebob_read_block(struct fw_unit *unit, u64 addr, void *buf, int size)
{
	return snd_fw_transaction(unit, TCODE_READ_BLOCK_REQUEST,
				  BEBOB_ADDR_REG_INFO + addr,
				  buf, size, 0);
}