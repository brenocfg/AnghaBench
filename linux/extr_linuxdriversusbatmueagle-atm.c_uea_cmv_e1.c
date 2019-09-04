#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int function; int address; int /*<<< orphan*/  idx; int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {TYPE_1__ e1; } ;
struct uea_softc {TYPE_2__ cmv_dsc; } ;
struct cmv_e1 {int bFunction; int /*<<< orphan*/  dwData; void* wOffsetAddress; int /*<<< orphan*/  dwSymbolicAddress; void* wIndex; int /*<<< orphan*/  bDirection; void* wPreamble; } ;
typedef  int /*<<< orphan*/  cmv ;

/* Variables and functions */
 int /*<<< orphan*/  E1_FUNCTION_SUBTYPE (int) ; 
 int /*<<< orphan*/  E1_FUNCTION_TYPE (int) ; 
 int /*<<< orphan*/  E1_GETSA1 (int) ; 
 int /*<<< orphan*/  E1_GETSA2 (int) ; 
 int /*<<< orphan*/  E1_GETSA3 (int) ; 
 int /*<<< orphan*/  E1_GETSA4 (int) ; 
 int /*<<< orphan*/  E1_HOSTTOMODEM ; 
 int /*<<< orphan*/  E1_PREAMBLE ; 
 int /*<<< orphan*/  INS_TO_USBDEV (struct uea_softc*) ; 
 int /*<<< orphan*/  UEA_E1_SET_BLOCK ; 
 int /*<<< orphan*/  UEA_MPTX_START ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uea_enters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uea_leaves (int /*<<< orphan*/ ) ; 
 int uea_request (struct uea_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct cmv_e1*) ; 
 int /*<<< orphan*/  uea_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int wait_cmv_ack (struct uea_softc*) ; 

__attribute__((used)) static int uea_cmv_e1(struct uea_softc *sc,
		u8 function, u32 address, u16 offset, u32 data)
{
	struct cmv_e1 cmv;
	int ret;

	uea_enters(INS_TO_USBDEV(sc));
	uea_vdbg(INS_TO_USBDEV(sc), "Function : %d-%d, Address : %c%c%c%c, "
			"offset : 0x%04x, data : 0x%08x\n",
			E1_FUNCTION_TYPE(function),
			E1_FUNCTION_SUBTYPE(function),
			E1_GETSA1(address), E1_GETSA2(address),
			E1_GETSA3(address),
			E1_GETSA4(address), offset, data);

	/* we send a request, but we expect a reply */
	sc->cmv_dsc.e1.function = function | 0x2;
	sc->cmv_dsc.e1.idx++;
	sc->cmv_dsc.e1.address = address;
	sc->cmv_dsc.e1.offset = offset;

	cmv.wPreamble = cpu_to_le16(E1_PREAMBLE);
	cmv.bDirection = E1_HOSTTOMODEM;
	cmv.bFunction = function;
	cmv.wIndex = cpu_to_le16(sc->cmv_dsc.e1.idx);
	put_unaligned_le32(address, &cmv.dwSymbolicAddress);
	cmv.wOffsetAddress = cpu_to_le16(offset);
	put_unaligned_le32(data >> 16 | data << 16, &cmv.dwData);

	ret = uea_request(sc, UEA_E1_SET_BLOCK, UEA_MPTX_START,
							sizeof(cmv), &cmv);
	if (ret < 0)
		return ret;
	ret = wait_cmv_ack(sc);
	uea_leaves(INS_TO_USBDEV(sc));
	return ret;
}