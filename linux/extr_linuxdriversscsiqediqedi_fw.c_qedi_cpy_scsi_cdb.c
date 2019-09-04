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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct scsi_cmnd {int cmd_len; scalar_t__ cmnd; } ;
typedef  int /*<<< orphan*/  dword ;

/* Variables and functions */
 int cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int*,void const*,int) ; 

__attribute__((used)) static void qedi_cpy_scsi_cdb(struct scsi_cmnd *sc, u32 *dstp)
{
	u32 dword;
	int lpcnt;
	u8 *srcp;

	lpcnt = sc->cmd_len / sizeof(dword);
	srcp = (u8 *)sc->cmnd;
	while (lpcnt--) {
		memcpy(&dword, (const void *)srcp, 4);
		*dstp = cpu_to_be32(dword);
		srcp += 4;
		dstp++;
	}
	if (sc->cmd_len & 0x3) {
		dword = (u32)srcp[0] | ((u32)srcp[1] << 8);
		*dstp = cpu_to_be32(dword);
	}
}