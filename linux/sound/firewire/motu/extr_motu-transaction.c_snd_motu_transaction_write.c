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
typedef  scalar_t__ u32 ;
struct snd_motu {int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SND_MOTU_ADDR_BASE ; 
 int TCODE_WRITE_BLOCK_REQUEST ; 
 int TCODE_WRITE_QUADLET_REQUEST ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

int snd_motu_transaction_write(struct snd_motu *motu, u32 offset, __be32 *reg,
			       size_t size)
{
	int tcode;

	if (size % sizeof(__be32) > 0 || size <= 0)
		return -EINVAL;
	if (size == sizeof(__be32))
		tcode = TCODE_WRITE_QUADLET_REQUEST;
	else
		tcode = TCODE_WRITE_BLOCK_REQUEST;

	return snd_fw_transaction(motu->unit, tcode,
				  SND_MOTU_ADDR_BASE + offset, reg, size, 0);
}