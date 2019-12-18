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
typedef  scalar_t__ u32 ;
struct snd_dice {int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCODE_READ_BLOCK_REQUEST ; 
 int /*<<< orphan*/  TCODE_READ_QUADLET_REQUEST ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int read_transaction(struct snd_dice *dice, u64 section_addr,
				   u32 offset, void *buf, size_t len)
{
	return snd_fw_transaction(dice->unit,
				  len == 4 ? TCODE_READ_QUADLET_REQUEST :
					     TCODE_READ_BLOCK_REQUEST,
				  section_addr + offset, buf, len, 0);
}