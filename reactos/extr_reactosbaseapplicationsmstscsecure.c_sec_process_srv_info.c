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
 int /*<<< orphan*/  DEBUG_RDP5 (char*) ; 
 int /*<<< orphan*/  RDP_V4 ; 
 int /*<<< orphan*/  g_rdp_version ; 
 int g_server_depth ; 
 int g_server_rdp_version ; 
 int /*<<< orphan*/  in_uint16_le (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sec_process_srv_info(STREAM s)
{
	in_uint16_le(s, g_server_rdp_version);
	DEBUG_RDP5(("Server RDP version is %d\n", g_server_rdp_version));
	if (1 == g_server_rdp_version)
	{
		g_rdp_version = RDP_V4;
		g_server_depth = 8;
	}
}