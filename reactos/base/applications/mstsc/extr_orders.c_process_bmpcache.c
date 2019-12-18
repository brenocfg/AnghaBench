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
typedef  int uint16 ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  RD_HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 scalar_t__ RDP_V5 ; 
 scalar_t__ bitmap_decompress (int*,int,int,int*,int,int) ; 
 int /*<<< orphan*/  cache_put_bitmap (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ g_rdp_version ; 
 int /*<<< orphan*/  in_uint16_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_uint8p (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  ui_create_bitmap (int,int,int*) ; 
 int /*<<< orphan*/  xfree (int*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
process_bmpcache(STREAM s)
{
	RD_HBITMAP bitmap;
	uint16 cache_idx, size;
	uint8 cache_id, width, height, bpp, Bpp;
	uint8 *data, *bmpdata;
	uint16 bufsize, pad2, row_size, final_size;
	uint8 pad1;

	pad2 = row_size = final_size = 0xffff;	/* Shut the compiler up */

	in_uint8(s, cache_id);
	in_uint8(s, pad1);	/* pad */
	in_uint8(s, width);
	in_uint8(s, height);
	in_uint8(s, bpp);
	Bpp = (bpp + 7) / 8;
	in_uint16_le(s, bufsize);	/* bufsize */
	in_uint16_le(s, cache_idx);

	if (g_rdp_version >= RDP_V5)
	{
		size = bufsize;
	}
	else
	{

		/* Begin compressedBitmapData */
		in_uint16_le(s, pad2);	/* pad */
		in_uint16_le(s, size);
		/*      in_uint8s(s, 4);  *//* row_size, final_size */
		in_uint16_le(s, row_size);
		in_uint16_le(s, final_size);

	}
	in_uint8p(s, data, size);

	DEBUG(("BMPCACHE(cx=%d,cy=%d,id=%d,idx=%d,bpp=%d,size=%d,pad1=%d,bufsize=%d,pad2=%d,rs=%d,fs=%d)\n", width, height, cache_id, cache_idx, bpp, size, pad1, bufsize, pad2, row_size, final_size));

	bmpdata = (uint8 *) xmalloc(width * height * Bpp);

	if (bitmap_decompress(bmpdata, width, height, data, size, Bpp))
	{
		bitmap = ui_create_bitmap(width, height, bmpdata);
		cache_put_bitmap(cache_id, cache_idx, bitmap);
	}
	else
	{
		DEBUG(("Failed to decompress bitmap data\n"));
	}
	if (pad1 || pad2) {}

	xfree(bmpdata);
}