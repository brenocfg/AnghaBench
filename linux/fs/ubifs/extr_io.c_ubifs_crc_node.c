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
typedef  int /*<<< orphan*/  uint32_t ;
struct ubifs_info {int dummy; } ;
struct ubifs_ch {int /*<<< orphan*/  crc; } ;

/* Variables and functions */
 int /*<<< orphan*/  UBIFS_CRC32_INIT ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,void*,int) ; 

void ubifs_crc_node(struct ubifs_info *c, void *node, int len)
{
	struct ubifs_ch *ch = node;
	uint32_t crc;

	crc = crc32(UBIFS_CRC32_INIT, node + 8, len - 8);
	ch->crc = cpu_to_le32(crc);
}