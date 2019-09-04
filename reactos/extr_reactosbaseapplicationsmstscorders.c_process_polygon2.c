#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  int uint32 ;
struct TYPE_11__ {int /*<<< orphan*/  style; } ;
struct TYPE_10__ {int opcode; int fillmode; int npoints; int datasize; int* data; int /*<<< orphan*/  fgcolour; int /*<<< orphan*/  bgcolour; void* y; void* x; TYPE_5__ brush; } ;
struct TYPE_9__ {void* y; void* x; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_1__ RD_POINT ;
typedef  int /*<<< orphan*/  RD_BOOL ;
typedef  TYPE_2__ POLYGON2_ORDER ;
typedef  int /*<<< orphan*/  BRUSH ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_uint8a (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* parse_delta (int*,int*) ; 
 int /*<<< orphan*/  rdp_in_colour (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdp_in_coord (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_parse_brush (int /*<<< orphan*/ ,TYPE_5__*,int) ; 
 int /*<<< orphan*/  setup_brush (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  ui_polygon (int,int,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
process_polygon2(STREAM s, POLYGON2_ORDER * os, uint32 present, RD_BOOL delta)
{
	int index, data, next;
	uint8 flags = 0;
	RD_POINT *points;
	BRUSH brush;

	if (present & 0x0001)
		rdp_in_coord(s, &os->x, delta);

	if (present & 0x0002)
		rdp_in_coord(s, &os->y, delta);

	if (present & 0x0004)
		in_uint8(s, os->opcode);

	if (present & 0x0008)
		in_uint8(s, os->fillmode);

	if (present & 0x0010)
		rdp_in_colour(s, &os->bgcolour);

	if (present & 0x0020)
		rdp_in_colour(s, &os->fgcolour);

	rdp_parse_brush(s, &os->brush, present >> 6);

	if (present & 0x0800)
		in_uint8(s, os->npoints);

	if (present & 0x1000)
	{
		in_uint8(s, os->datasize);
		in_uint8a(s, os->data, os->datasize);
	}

	DEBUG(("POLYGON2(x=%d,y=%d,op=0x%x,fm=%d,bs=%d,bg=0x%x,fg=0x%x,n=%d,sz=%d)\n",
	       os->x, os->y, os->opcode, os->fillmode, os->brush.style, os->bgcolour, os->fgcolour,
	       os->npoints, os->datasize));

	DEBUG(("Data: "));

	for (index = 0; index < os->datasize; index++)
		DEBUG(("%02x ", os->data[index]));

	DEBUG(("\n"));

	if (os->opcode < 0x01 || os->opcode > 0x10)
	{
		error("bad ROP2 0x%x\n", os->opcode);
		return;
	}

	setup_brush(&brush, &os->brush);

	points = (RD_POINT *) xmalloc((os->npoints + 1) * sizeof(RD_POINT));
	memset(points, 0, (os->npoints + 1) * sizeof(RD_POINT));

	points[0].x = os->x;
	points[0].y = os->y;

	index = 0;
	data = ((os->npoints - 1) / 4) + 1;
	for (next = 1; (next <= os->npoints) && (next < 256) && (data < os->datasize); next++)
	{
		if ((next - 1) % 4 == 0)
			flags = os->data[index++];

		if (~flags & 0x80)
			points[next].x = parse_delta(os->data, &data);

		if (~flags & 0x40)
			points[next].y = parse_delta(os->data, &data);

		flags <<= 2;
	}

	if (next - 1 == os->npoints)
		ui_polygon(os->opcode - 1, os->fillmode, points, os->npoints + 1,
			   &brush, os->bgcolour, os->fgcolour);
	else
		error("polygon2 parse error\n");

	xfree(points);
}