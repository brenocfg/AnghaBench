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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 scalar_t__ False ; 
 int RDP_CAPLEN_ORDER ; 
 int RDP_CAPSET_ORDER ; 
 scalar_t__ g_bitmap_cache ; 
 scalar_t__ g_desktop_save ; 
 scalar_t__ g_polygon_ellipse_orders ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8p (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  out_uint8s (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rdp_out_order_caps(STREAM s)
{
	uint8 order_caps[32];

	memset(order_caps, 0, 32);
	order_caps[0] = 1;	/* dest blt */
	order_caps[1] = 1;	/* pat blt */
	order_caps[2] = 1;	/* screen blt */
	order_caps[3] = (g_bitmap_cache ? 1 : 0);	/* memblt */
	order_caps[4] = 0;	/* triblt */
	order_caps[8] = 1;	/* line */
	order_caps[9] = 1;	/* line */
	order_caps[10] = 1;	/* rect */
	order_caps[11] = (g_desktop_save ? 1 : 0);	/* desksave */
	order_caps[13] = 1;	/* memblt */
	order_caps[14] = 1;	/* triblt */
	order_caps[20] = (g_polygon_ellipse_orders ? 1 : 0);	/* polygon */
	order_caps[21] = (g_polygon_ellipse_orders ? 1 : 0);	/* polygon2 */
	order_caps[22] = 1;	/* polyline */
	order_caps[25] = (g_polygon_ellipse_orders ? 1 : 0);	/* ellipse */
	order_caps[26] = (g_polygon_ellipse_orders ? 1 : 0);	/* ellipse2 */
	order_caps[27] = 1;	/* text2 */
	out_uint16_le(s, RDP_CAPSET_ORDER);
	out_uint16_le(s, RDP_CAPLEN_ORDER);

	out_uint8s(s, 20);	/* Terminal desc, pad */
	out_uint16_le(s, 1);	/* Cache X granularity */
	out_uint16_le(s, 20);	/* Cache Y granularity */
	out_uint16(s, 0);	/* Pad */
	out_uint16_le(s, 1);	/* Max order level */
	out_uint16_le(s, 0x147);	/* Number of fonts */
	out_uint16_le(s, 0x2a);	/* Capability flags */
	out_uint8p(s, order_caps, 32);	/* Orders supported */
	out_uint16_le(s, 0x6a1);	/* Text capability flags */
	out_uint8s(s, 6);	/* Pad */
	out_uint32_le(s, g_desktop_save == False ? 0 : 0x38400);	/* Desktop cache size */
	out_uint32(s, 0);	/* Unknown */
	out_uint32_le(s, 0x4e4);	/* Unknown */
}