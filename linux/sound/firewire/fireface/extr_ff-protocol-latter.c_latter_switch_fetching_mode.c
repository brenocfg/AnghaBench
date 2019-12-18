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
typedef  int u32 ;
struct snd_ff {int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  LATTER_FETCH_MODE ; 
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int latter_switch_fetching_mode(struct snd_ff *ff, bool enable)
{
	u32 data;
	__le32 reg;

	if (enable)
		data = 0x00000000;
	else
		data = 0xffffffff;
	reg = cpu_to_le32(data);

	return snd_fw_transaction(ff->unit, TCODE_WRITE_QUADLET_REQUEST,
				  LATTER_FETCH_MODE, &reg, sizeof(reg), 0);
}