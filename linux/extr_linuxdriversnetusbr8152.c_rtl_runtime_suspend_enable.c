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
typedef  int /*<<< orphan*/  u32 ;
struct r8152 {int /*<<< orphan*/  saved_wolopts; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRWECR_CONFIG ; 
 int /*<<< orphan*/  CRWECR_NORAML ; 
 int /*<<< orphan*/  LINK_OFF_WAKE_EN ; 
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int /*<<< orphan*/  PLA_CONFIG34 ; 
 int /*<<< orphan*/  PLA_CRWECR ; 
 int /*<<< orphan*/  WAKE_ANY ; 
 int /*<<< orphan*/  __rtl_set_wol (struct r8152*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_read_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_write_byte (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_write_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl_runtime_suspend_enable(struct r8152 *tp, bool enable)
{
	if (enable) {
		u32 ocp_data;

		__rtl_set_wol(tp, WAKE_ANY);

		ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_CONFIG);

		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CONFIG34);
		ocp_data |= LINK_OFF_WAKE_EN;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_CONFIG34, ocp_data);

		ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);
	} else {
		u32 ocp_data;

		__rtl_set_wol(tp, tp->saved_wolopts);

		ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_CONFIG);

		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CONFIG34);
		ocp_data &= ~LINK_OFF_WAKE_EN;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_CONFIG34, ocp_data);

		ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);
	}
}