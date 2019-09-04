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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_3__ {int function; int offset; int address; int group; } ;
struct TYPE_4__ {TYPE_1__ e4; } ;
struct uea_softc {TYPE_2__ cmv_dsc; } ;
struct cmv_e4 {int /*<<< orphan*/ * dwData; void* wOffset; void* wAddress; void* wGroup; void* wFunction; } ;
typedef  int /*<<< orphan*/  cmv ;

/* Variables and functions */
 int /*<<< orphan*/  E4_FUNCTION_SUBTYPE (int) ; 
 int /*<<< orphan*/  E4_FUNCTION_TYPE (int) ; 
 int /*<<< orphan*/  INS_TO_USBDEV (struct uea_softc*) ; 
 int /*<<< orphan*/  UEA_E4_SET_BLOCK ; 
 int /*<<< orphan*/  UEA_MPTX_START ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cmv_e4*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uea_enters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uea_leaves (int /*<<< orphan*/ ) ; 
 int uea_request (struct uea_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct cmv_e4*) ; 
 int /*<<< orphan*/  uea_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int wait_cmv_ack (struct uea_softc*) ; 

__attribute__((used)) static int uea_cmv_e4(struct uea_softc *sc,
		u16 function, u16 group, u16 address, u16 offset, u32 data)
{
	struct cmv_e4 cmv;
	int ret;

	uea_enters(INS_TO_USBDEV(sc));
	memset(&cmv, 0, sizeof(cmv));

	uea_vdbg(INS_TO_USBDEV(sc), "Function : %d-%d, Group : 0x%04x, "
		 "Address : 0x%04x, offset : 0x%04x, data : 0x%08x\n",
		 E4_FUNCTION_TYPE(function), E4_FUNCTION_SUBTYPE(function),
		 group, address, offset, data);

	/* we send a request, but we expect a reply */
	sc->cmv_dsc.e4.function = function | (0x1 << 4);
	sc->cmv_dsc.e4.offset = offset;
	sc->cmv_dsc.e4.address = address;
	sc->cmv_dsc.e4.group = group;

	cmv.wFunction = cpu_to_be16(function);
	cmv.wGroup = cpu_to_be16(group);
	cmv.wAddress = cpu_to_be16(address);
	cmv.wOffset = cpu_to_be16(offset);
	cmv.dwData[0] = cpu_to_be32(data);

	ret = uea_request(sc, UEA_E4_SET_BLOCK, UEA_MPTX_START,
							sizeof(cmv), &cmv);
	if (ret < 0)
		return ret;
	ret = wait_cmv_ack(sc);
	uea_leaves(INS_TO_USBDEV(sc));
	return ret;
}