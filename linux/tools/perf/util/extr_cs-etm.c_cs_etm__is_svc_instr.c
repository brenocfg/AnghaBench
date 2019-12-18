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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct cs_etm_queue {int dummy; } ;
struct cs_etm_packet {int isa; } ;
typedef  int /*<<< orphan*/  instr32 ;
typedef  int /*<<< orphan*/  instr16 ;

/* Variables and functions */
#define  CS_ETM_ISA_A32 131 
#define  CS_ETM_ISA_A64 130 
#define  CS_ETM_ISA_T32 129 
#define  CS_ETM_ISA_UNKNOWN 128 
 int /*<<< orphan*/  cs_etm__mem_access (struct cs_etm_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool cs_etm__is_svc_instr(struct cs_etm_queue *etmq, u8 trace_chan_id,
				 struct cs_etm_packet *packet,
				 u64 end_addr)
{
	/* Initialise to keep compiler happy */
	u16 instr16 = 0;
	u32 instr32 = 0;
	u64 addr;

	switch (packet->isa) {
	case CS_ETM_ISA_T32:
		/*
		 * The SVC of T32 is defined in ARM DDI 0487D.a, F5.1.247:
		 *
		 *  b'15         b'8
		 * +-----------------+--------+
		 * | 1 1 0 1 1 1 1 1 |  imm8  |
		 * +-----------------+--------+
		 *
		 * According to the specifiction, it only defines SVC for T32
		 * with 16 bits instruction and has no definition for 32bits;
		 * so below only read 2 bytes as instruction size for T32.
		 */
		addr = end_addr - 2;
		cs_etm__mem_access(etmq, trace_chan_id, addr,
				   sizeof(instr16), (u8 *)&instr16);
		if ((instr16 & 0xFF00) == 0xDF00)
			return true;

		break;
	case CS_ETM_ISA_A32:
		/*
		 * The SVC of A32 is defined in ARM DDI 0487D.a, F5.1.247:
		 *
		 *  b'31 b'28 b'27 b'24
		 * +---------+---------+-------------------------+
		 * |  !1111  | 1 1 1 1 |        imm24            |
		 * +---------+---------+-------------------------+
		 */
		addr = end_addr - 4;
		cs_etm__mem_access(etmq, trace_chan_id, addr,
				   sizeof(instr32), (u8 *)&instr32);
		if ((instr32 & 0x0F000000) == 0x0F000000 &&
		    (instr32 & 0xF0000000) != 0xF0000000)
			return true;

		break;
	case CS_ETM_ISA_A64:
		/*
		 * The SVC of A64 is defined in ARM DDI 0487D.a, C6.2.294:
		 *
		 *  b'31               b'21           b'4     b'0
		 * +-----------------------+---------+-----------+
		 * | 1 1 0 1 0 1 0 0 0 0 0 |  imm16  | 0 0 0 0 1 |
		 * +-----------------------+---------+-----------+
		 */
		addr = end_addr - 4;
		cs_etm__mem_access(etmq, trace_chan_id, addr,
				   sizeof(instr32), (u8 *)&instr32);
		if ((instr32 & 0xFFE0001F) == 0xd4000001)
			return true;

		break;
	case CS_ETM_ISA_UNKNOWN:
	default:
		break;
	}

	return false;
}