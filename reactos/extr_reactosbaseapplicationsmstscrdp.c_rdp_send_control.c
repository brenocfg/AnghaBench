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
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  RDP_DATA_PDU_CONTROL ; 
 int /*<<< orphan*/  out_uint16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_init_data (int) ; 
 int /*<<< orphan*/  rdp_send_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rdp_send_control(uint16 action)
{
	STREAM s;

	s = rdp_init_data(8);

	out_uint16_le(s, action);
	out_uint16(s, 0);	/* userid */
	out_uint32(s, 0);	/* control id */

	s_mark_end(s);
	rdp_send_data(s, RDP_DATA_PDU_CONTROL);
}