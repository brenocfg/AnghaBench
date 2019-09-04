#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_6__ {int /*<<< orphan*/  colour; } ;
struct TYPE_5__ {int opcode; TYPE_2__ pen; int /*<<< orphan*/  endy; int /*<<< orphan*/  endx; int /*<<< orphan*/  starty; int /*<<< orphan*/  startx; int /*<<< orphan*/  bgcolour; int /*<<< orphan*/  mixmode; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  RD_BOOL ;
typedef  TYPE_1__ LINE_ORDER ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/  in_uint16_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdp_in_colour (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdp_in_coord (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_parse_pen (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ui_line (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void
process_line(STREAM s, LINE_ORDER * os, uint32 present, RD_BOOL delta)
{
	if (present & 0x0001)
		in_uint16_le(s, os->mixmode);

	if (present & 0x0002)
		rdp_in_coord(s, &os->startx, delta);

	if (present & 0x0004)
		rdp_in_coord(s, &os->starty, delta);

	if (present & 0x0008)
		rdp_in_coord(s, &os->endx, delta);

	if (present & 0x0010)
		rdp_in_coord(s, &os->endy, delta);

	if (present & 0x0020)
		rdp_in_colour(s, &os->bgcolour);

	if (present & 0x0040)
		in_uint8(s, os->opcode);

	rdp_parse_pen(s, &os->pen, present >> 7);

	DEBUG(("LINE(op=0x%x,sx=%d,sy=%d,dx=%d,dy=%d,fg=0x%x)\n",
	       os->opcode, os->startx, os->starty, os->endx, os->endy, os->pen.colour));

	if (os->opcode < 0x01 || os->opcode > 0x10)
	{
		error("bad ROP2 0x%x\n", os->opcode);
		return;
	}

	ui_line(os->opcode - 1, os->startx, os->starty, os->endx, os->endy, &os->pen);
}