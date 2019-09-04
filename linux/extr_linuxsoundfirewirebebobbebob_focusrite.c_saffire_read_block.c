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
typedef  int /*<<< orphan*/  u32 ;
struct snd_bebob {int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ SAFFIRE_ADDRESS_BASE ; 
 int /*<<< orphan*/  TCODE_READ_BLOCK_REQUEST ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
saffire_read_block(struct snd_bebob *bebob, u64 offset,
		   u32 *buf, unsigned int size)
{
	unsigned int i;
	int err;
	__be32 *tmp = (__be32 *)buf;

	err =  snd_fw_transaction(bebob->unit, TCODE_READ_BLOCK_REQUEST,
				  SAFFIRE_ADDRESS_BASE + offset,
				  tmp, size, 0);
	if (err < 0)
		goto end;

	for (i = 0; i < size / sizeof(u32); i++)
		buf[i] = be32_to_cpu(tmp[i]);
end:
	return err;
}