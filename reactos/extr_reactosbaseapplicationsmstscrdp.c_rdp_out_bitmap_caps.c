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
 int RDP_CAPLEN_BITMAP ; 
 int RDP_CAPSET_BITMAP ; 
 scalar_t__ g_bitmap_compression ; 
 int g_server_depth ; 
 int /*<<< orphan*/  out_uint16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rdp_out_bitmap_caps(STREAM s)
{
	out_uint16_le(s, RDP_CAPSET_BITMAP);
	out_uint16_le(s, RDP_CAPLEN_BITMAP);

	out_uint16_le(s, g_server_depth);	/* Preferred colour depth */
	out_uint16_le(s, 1);	/* Receive 1 BPP */
	out_uint16_le(s, 1);	/* Receive 4 BPP */
	out_uint16_le(s, 1);	/* Receive 8 BPP */
	out_uint16_le(s, 800);	/* Desktop width */
	out_uint16_le(s, 600);	/* Desktop height */
	out_uint16(s, 0);	/* Pad */
	out_uint16(s, 1);	/* Allow resize */
	out_uint16_le(s, g_bitmap_compression ? 1 : 0);	/* Support compression */
	out_uint16(s, 0);	/* Unknown */
	out_uint16_le(s, 1);	/* Unknown */
	out_uint16(s, 0);	/* Pad */
}