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
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  RD_HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  cache_put_bitmap (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_uint16_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_uint8p (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_uint8s (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  ui_create_bitmap (int,int,int*) ; 
 int /*<<< orphan*/  xfree (int*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
process_raw_bmpcache(STREAM s)
{
	RD_HBITMAP bitmap;
	uint16 cache_idx, bufsize;
	uint8 cache_id, width, height, bpp, Bpp;
	uint8 *data, *inverted;
	int y;

	in_uint8(s, cache_id);
	in_uint8s(s, 1);	/* pad */
	in_uint8(s, width);
	in_uint8(s, height);
	in_uint8(s, bpp);
	Bpp = (bpp + 7) / 8;
	in_uint16_le(s, bufsize);
	in_uint16_le(s, cache_idx);
	in_uint8p(s, data, bufsize);

	DEBUG(("RAW_BMPCACHE(cx=%d,cy=%d,id=%d,idx=%d)\n", width, height, cache_id, cache_idx));
	inverted = (uint8 *) xmalloc(width * height * Bpp);
	for (y = 0; y < height; y++)
	{
		memcpy(&inverted[(height - y - 1) * (width * Bpp)], &data[y * (width * Bpp)],
		       width * Bpp);
	}

	bitmap = ui_create_bitmap(width, height, inverted);
	xfree(inverted);
	cache_put_bitmap(cache_id, cache_idx, bitmap);
}