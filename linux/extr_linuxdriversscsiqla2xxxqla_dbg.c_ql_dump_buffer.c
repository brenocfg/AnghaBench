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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int /*<<< orphan*/  KERN_CONT ; 
 int /*<<< orphan*/  min (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ql_mask_match (int /*<<< orphan*/ ) ; 

void
ql_dump_buffer(uint32_t level, scsi_qla_host_t *vha, int32_t id,
	uint8_t *buf, uint size)
{
	uint cnt;

	if (!ql_mask_match(level))
		return;

	ql_dbg(level, vha, id,
	    "%-+5d  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n", size);
	ql_dbg(level, vha, id,
	    "----- -----------------------------------------------\n");
	for (cnt = 0; cnt < size; cnt += 16) {
		ql_dbg(level, vha, id, "%04x: ", cnt);
		print_hex_dump(KERN_CONT, "", DUMP_PREFIX_NONE, 16, 1,
			       buf + cnt, min(16U, size - cnt), false);
	}
}