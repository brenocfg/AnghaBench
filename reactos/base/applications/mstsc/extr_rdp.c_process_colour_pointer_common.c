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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint16 ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  RD_HCURSOR ;

/* Variables and functions */
 int MIN (int,int) ; 
 int /*<<< orphan*/  cache_put_cursor (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_uint16_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_uint8p (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ui_create_cursor (int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ui_set_cursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,int,int) ; 

__attribute__((used)) static void
process_colour_pointer_common(STREAM s, int bpp)
{
	uint16 width, height, cache_idx, masklen, datalen;
	uint16 x, y;
	uint8 *mask;
	uint8 *data;
	RD_HCURSOR cursor;

	in_uint16_le(s, cache_idx);
	in_uint16_le(s, x);
	in_uint16_le(s, y);
	in_uint16_le(s, width);
	in_uint16_le(s, height);
	in_uint16_le(s, masklen);
	in_uint16_le(s, datalen);
	in_uint8p(s, data, datalen);
	in_uint8p(s, mask, masklen);
	if ((width != 32) || (height != 32))
	{
		warning("process_colour_pointer_common: " "width %d height %d\n", width, height);
	}

	/* keep hotspot within cursor bounding box */
	x = MIN(x, width - 1);
	y = MIN(y, height - 1);
	cursor = ui_create_cursor(x, y, width, height, mask, data, bpp);
	ui_set_cursor(cursor);
	cache_put_cursor(cache_idx, cursor);
}