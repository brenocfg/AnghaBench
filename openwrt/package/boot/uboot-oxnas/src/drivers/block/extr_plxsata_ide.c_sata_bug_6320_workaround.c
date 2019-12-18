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
typedef  int /*<<< orphan*/  ulong ;

/* Variables and functions */
 int ATA_SECT_SIZE ; 
 unsigned long SATA_CORE_PORT0_DATA_DIR ; 
 unsigned long SATA_CORE_PORT1_DATA_DIR ; 
 scalar_t__ SATA_DATACOUNT_PORT0 ; 
 scalar_t__ SATA_DATACOUNT_PORT1 ; 
 scalar_t__ SATA_DATA_MUX_RAM0 ; 
 scalar_t__ SATA_DATA_MUX_RAM1 ; 
 scalar_t__ SATA_DM_DBG1 ; 
 int /*<<< orphan*/  debug (char*,int,int,int) ; 

__attribute__((used)) static void sata_bug_6320_workaround(int port, ulong *candidate)
{
	int is_read;
	int quads_transferred;
	int remainder;
	int sector_quads_remaining;

	/* Only want to apply fix to reads */
	is_read = !(*((unsigned long*) SATA_DM_DBG1)
		& (port ? SATA_CORE_PORT1_DATA_DIR : SATA_CORE_PORT0_DATA_DIR));

	/* Check for an incomplete transfer, i.e. not a multiple of 512 bytes
	 transferred (datacount_port register counts quads transferred) */
	quads_transferred = *((unsigned long*) (
		port ? SATA_DATACOUNT_PORT1 : SATA_DATACOUNT_PORT0));

	remainder = quads_transferred & 0x7f;
	sector_quads_remaining = remainder ? (0x80 - remainder) : 0;

	if (is_read && (sector_quads_remaining == 2)) {
		debug("SATA read fixup, only transfered %d quads, "
			"sector_quads_remaining %d, port %d\n",
			quads_transferred, sector_quads_remaining, port);

		int total_len = ATA_SECT_SIZE;
		ulong *sata_data_ptr = (void*) (
			port ? SATA_DATA_MUX_RAM1 : SATA_DATA_MUX_RAM0)
			+ ((total_len - 8) % 2048);

		*candidate = *sata_data_ptr;
		*(candidate + 1) = *(sata_data_ptr + 1);
	}
}