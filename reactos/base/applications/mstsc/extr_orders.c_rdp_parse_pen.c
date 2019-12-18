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
struct TYPE_3__ {int /*<<< orphan*/  colour; int /*<<< orphan*/  width; int /*<<< orphan*/  style; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  RD_BOOL ;
typedef  TYPE_1__ PEN ;

/* Variables and functions */
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_in_colour (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_check (int /*<<< orphan*/ ) ; 

__attribute__((used)) static RD_BOOL
rdp_parse_pen(STREAM s, PEN * pen, uint32 present)
{
	if (present & 1)
		in_uint8(s, pen->style);

	if (present & 2)
		in_uint8(s, pen->width);

	if (present & 4)
		rdp_in_colour(s, &pen->colour);

	return s_check(s);
}