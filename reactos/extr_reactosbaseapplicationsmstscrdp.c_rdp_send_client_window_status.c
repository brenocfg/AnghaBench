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
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  RDP_DATA_PDU_CLIENT_WINDOW_STATUS ; 
 int /*<<< orphan*/  g_height ; 
 int /*<<< orphan*/  g_width ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdp_init_data (int) ; 
 int /*<<< orphan*/  rdp_send_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ ) ; 

void
rdp_send_client_window_status(int status)
{
	STREAM s;
	static int current_status = 1;

	if (current_status == status)
		return;

	s = rdp_init_data(12);

	out_uint32_le(s, status);

	switch (status)
	{
		case 0:	/* shut the server up */
			break;

		case 1:	/* receive data again */
			out_uint32_le(s, 0);	/* unknown */
			out_uint16_le(s, g_width);
			out_uint16_le(s, g_height);
			break;
	}

	s_mark_end(s);
	rdp_send_data(s, RDP_DATA_PDU_CLIENT_WINDOW_STATUS);
	current_status = status;
}