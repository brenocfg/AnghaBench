#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_3__ {int /*<<< orphan*/  srcy; int /*<<< orphan*/  srcx; int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  opcode; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_1__ SCREENBLT_ORDER ;
typedef  int /*<<< orphan*/  RD_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  ROP2_S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_in_coord (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_screenblt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_screenblt(STREAM s, SCREENBLT_ORDER * os, uint32 present, RD_BOOL delta)
{
	if (present & 0x0001)
		rdp_in_coord(s, &os->x, delta);

	if (present & 0x0002)
		rdp_in_coord(s, &os->y, delta);

	if (present & 0x0004)
		rdp_in_coord(s, &os->cx, delta);

	if (present & 0x0008)
		rdp_in_coord(s, &os->cy, delta);

	if (present & 0x0010)
		in_uint8(s, os->opcode);

	if (present & 0x0020)
		rdp_in_coord(s, &os->srcx, delta);

	if (present & 0x0040)
		rdp_in_coord(s, &os->srcy, delta);

	DEBUG(("SCREENBLT(op=0x%x,x=%d,y=%d,cx=%d,cy=%d,srcx=%d,srcy=%d)\n",
	       os->opcode, os->x, os->y, os->cx, os->cy, os->srcx, os->srcy));

	ui_screenblt(ROP2_S(os->opcode), os->x, os->y, os->cx, os->cy, os->srcx, os->srcy);
}