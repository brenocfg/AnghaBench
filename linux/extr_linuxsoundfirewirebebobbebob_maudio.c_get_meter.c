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
struct snd_bebob {int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 scalar_t__ MAUDIO_SPECIFIC_ADDRESS ; 
 scalar_t__ METER_OFFSET ; 
 int /*<<< orphan*/  TCODE_READ_BLOCK_REQUEST ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
get_meter(struct snd_bebob *bebob, void *buf, unsigned int size)
{
	return snd_fw_transaction(bebob->unit, TCODE_READ_BLOCK_REQUEST,
				  MAUDIO_SPECIFIC_ADDRESS + METER_OFFSET,
				  buf, size, 0);
}