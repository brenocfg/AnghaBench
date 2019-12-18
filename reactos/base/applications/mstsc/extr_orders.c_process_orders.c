#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int uint16 ;
struct TYPE_26__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
struct TYPE_25__ {int order_type; int /*<<< orphan*/  text2; int /*<<< orphan*/  ellipse2; int /*<<< orphan*/  ellipse; int /*<<< orphan*/  polyline; int /*<<< orphan*/  polygon2; int /*<<< orphan*/  polygon; int /*<<< orphan*/  triblt; int /*<<< orphan*/  memblt; int /*<<< orphan*/  desksave; int /*<<< orphan*/  rect; int /*<<< orphan*/  line; int /*<<< orphan*/  screenblt; int /*<<< orphan*/  patblt; int /*<<< orphan*/  destblt; TYPE_4__ bounds; } ;
struct TYPE_24__ {scalar_t__ p; } ;
typedef  TYPE_1__* STREAM ;
typedef  int RD_BOOL ;
typedef  TYPE_2__ RDP_ORDER_STATE ;

/* Variables and functions */
 int RDP_ORDER_BOUNDS ; 
 int RDP_ORDER_CHANGE ; 
 int RDP_ORDER_DELTA ; 
#define  RDP_ORDER_DESKSAVE 141 
#define  RDP_ORDER_DESTBLT 140 
#define  RDP_ORDER_ELLIPSE 139 
#define  RDP_ORDER_ELLIPSE2 138 
 int RDP_ORDER_LASTBOUNDS ; 
#define  RDP_ORDER_LINE 137 
#define  RDP_ORDER_MEMBLT 136 
#define  RDP_ORDER_PATBLT 135 
#define  RDP_ORDER_POLYGON 134 
#define  RDP_ORDER_POLYGON2 133 
#define  RDP_ORDER_POLYLINE 132 
#define  RDP_ORDER_RECT 131 
#define  RDP_ORDER_SCREENBLT 130 
 int RDP_ORDER_SECONDARY ; 
 int RDP_ORDER_STANDARD ; 
#define  RDP_ORDER_TEXT2 129 
#define  RDP_ORDER_TRIBLT 128 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ g_next_packet ; 
 TYPE_2__ g_order_state ; 
 int /*<<< orphan*/  in_uint8 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  process_desksave (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_destblt (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_ellipse (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_ellipse2 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_line (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_memblt (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_patblt (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_polygon (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_polygon2 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_polyline (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_rect (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_screenblt (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_secondary_order (TYPE_1__*) ; 
 int /*<<< orphan*/  process_text2 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_triblt (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdp_in_present (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  rdp_parse_bounds (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ui_reset_clip () ; 
 int /*<<< orphan*/  ui_set_clip (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

void
process_orders(STREAM s, uint16 num_orders)
{
	RDP_ORDER_STATE *os = &g_order_state;
	uint32 present;
	uint8 order_flags;
	int size, processed = 0;
	RD_BOOL delta;

	while (processed < num_orders)
	{
		in_uint8(s, order_flags);

		if (!(order_flags & RDP_ORDER_STANDARD))
		{
			error("order parsing failed\n");
			break;
		}

		if (order_flags & RDP_ORDER_SECONDARY)
		{
			process_secondary_order(s);
		}
		else
		{
			if (order_flags & RDP_ORDER_CHANGE)
			{
				in_uint8(s, os->order_type);
			}

			switch (os->order_type)
			{
				case RDP_ORDER_TRIBLT:
				case RDP_ORDER_TEXT2:
					size = 3;
					break;

				case RDP_ORDER_PATBLT:
				case RDP_ORDER_MEMBLT:
				case RDP_ORDER_LINE:
				case RDP_ORDER_POLYGON2:
				case RDP_ORDER_ELLIPSE2:
					size = 2;
					break;

				default:
					size = 1;
			}

			rdp_in_present(s, &present, order_flags, size);

			if (order_flags & RDP_ORDER_BOUNDS)
			{
				if (!(order_flags & RDP_ORDER_LASTBOUNDS))
					rdp_parse_bounds(s, &os->bounds);

				ui_set_clip(os->bounds.left,
					    os->bounds.top,
					    os->bounds.right -
					    os->bounds.left + 1,
					    os->bounds.bottom - os->bounds.top + 1);
			}

			delta = order_flags & RDP_ORDER_DELTA;

			switch (os->order_type)
			{
				case RDP_ORDER_DESTBLT:
					process_destblt(s, &os->destblt, present, delta);
					break;

				case RDP_ORDER_PATBLT:
					process_patblt(s, &os->patblt, present, delta);
					break;

				case RDP_ORDER_SCREENBLT:
					process_screenblt(s, &os->screenblt, present, delta);
					break;

				case RDP_ORDER_LINE:
					process_line(s, &os->line, present, delta);
					break;

				case RDP_ORDER_RECT:
					process_rect(s, &os->rect, present, delta);
					break;

				case RDP_ORDER_DESKSAVE:
					process_desksave(s, &os->desksave, present, delta);
					break;

				case RDP_ORDER_MEMBLT:
					process_memblt(s, &os->memblt, present, delta);
					break;

				case RDP_ORDER_TRIBLT:
					process_triblt(s, &os->triblt, present, delta);
					break;

				case RDP_ORDER_POLYGON:
					process_polygon(s, &os->polygon, present, delta);
					break;

				case RDP_ORDER_POLYGON2:
					process_polygon2(s, &os->polygon2, present, delta);
					break;

				case RDP_ORDER_POLYLINE:
					process_polyline(s, &os->polyline, present, delta);
					break;

				case RDP_ORDER_ELLIPSE:
					process_ellipse(s, &os->ellipse, present, delta);
					break;

				case RDP_ORDER_ELLIPSE2:
					process_ellipse2(s, &os->ellipse2, present, delta);
					break;

				case RDP_ORDER_TEXT2:
					process_text2(s, &os->text2, present, delta);
					break;

				default:
					unimpl("order %d\n", os->order_type);
					return;
			}

			if (order_flags & RDP_ORDER_BOUNDS)
				ui_reset_clip();
		}

		processed++;
	}
#if 0
	/* not true when RDP_COMPRESSION is set */
	if (s->p != g_next_packet)
		error("%d bytes remaining\n", (int) (g_next_packet - s->p));
#endif

}