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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  RDP_CTL_COOPERATE ; 
 int /*<<< orphan*/  RDP_CTL_REQUEST_CONTROL ; 
 int /*<<< orphan*/  RDP_INPUT_SYNCHRONIZE ; 
 scalar_t__ RDP_V5 ; 
 scalar_t__ g_numlock_sync ; 
 int /*<<< orphan*/  g_rdp_shareid ; 
 scalar_t__ g_rdp_version ; 
 int /*<<< orphan*/  in_uint16_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_uint32_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_uint8s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_enum_bmpcache2 () ; 
 int /*<<< orphan*/  rdp_process_server_caps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_recv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdp_send_confirm_active () ; 
 int /*<<< orphan*/  rdp_send_control (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_send_fonts (int) ; 
 int /*<<< orphan*/  rdp_send_input (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_send_synchronise () ; 
 int /*<<< orphan*/  read_keyboard_state () ; 
 int /*<<< orphan*/  reset_order_state () ; 
 int /*<<< orphan*/  ui_get_numlock_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_demand_active(STREAM s)
{
	uint8 type;
	uint16 len_src_descriptor, len_combined_caps;

	in_uint32_le(s, g_rdp_shareid);
	in_uint16_le(s, len_src_descriptor);
	in_uint16_le(s, len_combined_caps);
	in_uint8s(s, len_src_descriptor);

	DEBUG(("DEMAND_ACTIVE(id=0x%x)\n", g_rdp_shareid));
	rdp_process_server_caps(s, len_combined_caps);

	rdp_send_confirm_active();
	rdp_send_synchronise();
	rdp_send_control(RDP_CTL_COOPERATE);
	rdp_send_control(RDP_CTL_REQUEST_CONTROL);
	rdp_recv(&type);	/* RDP_PDU_SYNCHRONIZE */
	rdp_recv(&type);	/* RDP_CTL_COOPERATE */
	rdp_recv(&type);	/* RDP_CTL_GRANT_CONTROL */
	rdp_send_input(0, RDP_INPUT_SYNCHRONIZE, 0,
		       g_numlock_sync ? ui_get_numlock_state(read_keyboard_state()) : 0, 0);

	if (g_rdp_version >= RDP_V5)
	{
		rdp_enum_bmpcache2();
		rdp_send_fonts(3);
	}
	else
	{
		rdp_send_fonts(1);
		rdp_send_fonts(2);
	}

	rdp_recv(&type);	/* RDP_PDU_UNKNOWN 0x28 (Fonts?) */
	reset_order_state();
}