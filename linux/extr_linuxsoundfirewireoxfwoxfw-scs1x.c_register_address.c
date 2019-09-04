#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct snd_oxfw {int /*<<< orphan*/  unit; struct fw_scs1x* spec; } ;
struct TYPE_2__ {int offset; } ;
struct fw_scs1x {TYPE_1__ hss_handler; } ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  HSS1394_ADDRESS ; 
 scalar_t__ HSS1394_TAG_CHANGE_ADDRESS ; 
 int /*<<< orphan*/  TCODE_WRITE_BLOCK_REQUEST ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int register_address(struct snd_oxfw *oxfw)
{
	struct fw_scs1x *scs = oxfw->spec;
	__be64 data;

	data = cpu_to_be64(((u64)HSS1394_TAG_CHANGE_ADDRESS << 56) |
			    scs->hss_handler.offset);
	return snd_fw_transaction(oxfw->unit, TCODE_WRITE_BLOCK_REQUEST,
				  HSS1394_ADDRESS, &data, sizeof(data), 0);
}