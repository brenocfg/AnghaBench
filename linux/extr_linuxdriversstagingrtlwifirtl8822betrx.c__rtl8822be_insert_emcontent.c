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
typedef  int u32 ;
struct rtl_tcb_desc {int empkt_num; int* empkt_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_EARLYMODE_LEN0 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_EARLYMODE_LEN1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_EARLYMODE_LEN2_1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_EARLYMODE_LEN2_2 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_EARLYMODE_LEN3 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_EARLYMODE_LEN4 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_EARLYMODE_PKTNUM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl8822be_insert_emcontent(struct rtl_tcb_desc *ptcb_desc,
					u8 *virtualaddress)
{
	u32 dwtmp = 0;

	memset(virtualaddress, 0, 8);

	SET_EARLYMODE_PKTNUM(virtualaddress, ptcb_desc->empkt_num);
	if (ptcb_desc->empkt_num == 1) {
		dwtmp = ptcb_desc->empkt_len[0];
	} else {
		dwtmp = ptcb_desc->empkt_len[0];
		dwtmp += ((dwtmp % 4) ? (4 - dwtmp % 4) : 0) + 4;
		dwtmp += ptcb_desc->empkt_len[1];
	}
	SET_EARLYMODE_LEN0(virtualaddress, dwtmp);

	if (ptcb_desc->empkt_num <= 3) {
		dwtmp = ptcb_desc->empkt_len[2];
	} else {
		dwtmp = ptcb_desc->empkt_len[2];
		dwtmp += ((dwtmp % 4) ? (4 - dwtmp % 4) : 0) + 4;
		dwtmp += ptcb_desc->empkt_len[3];
	}
	SET_EARLYMODE_LEN1(virtualaddress, dwtmp);
	if (ptcb_desc->empkt_num <= 5) {
		dwtmp = ptcb_desc->empkt_len[4];
	} else {
		dwtmp = ptcb_desc->empkt_len[4];
		dwtmp += ((dwtmp % 4) ? (4 - dwtmp % 4) : 0) + 4;
		dwtmp += ptcb_desc->empkt_len[5];
	}
	SET_EARLYMODE_LEN2_1(virtualaddress, dwtmp & 0xF);
	SET_EARLYMODE_LEN2_2(virtualaddress, dwtmp >> 4);
	if (ptcb_desc->empkt_num <= 7) {
		dwtmp = ptcb_desc->empkt_len[6];
	} else {
		dwtmp = ptcb_desc->empkt_len[6];
		dwtmp += ((dwtmp % 4) ? (4 - dwtmp % 4) : 0) + 4;
		dwtmp += ptcb_desc->empkt_len[7];
	}
	SET_EARLYMODE_LEN3(virtualaddress, dwtmp);
	if (ptcb_desc->empkt_num <= 9) {
		dwtmp = ptcb_desc->empkt_len[8];
	} else {
		dwtmp = ptcb_desc->empkt_len[8];
		dwtmp += ((dwtmp % 4) ? (4 - dwtmp % 4) : 0) + 4;
		dwtmp += ptcb_desc->empkt_len[9];
	}
	SET_EARLYMODE_LEN4(virtualaddress, dwtmp);
}