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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_3__ {int colour_code; int data_size; int* data; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_1__ BRUSHDATA ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  cache_put_brush_data (int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_uint8a (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  in_uint8p (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  process_compressed_8x8_brush_data (int*,int*,int) ; 
 int /*<<< orphan*/  warning (char*,int,int) ; 
 void* xmalloc (int) ; 

__attribute__((used)) static void
process_brushcache(STREAM s, uint16 flags)
{
	BRUSHDATA brush_data;
	uint8 cache_idx, colour_code, width, height, size, type;
	uint8 *comp_brush;
	int index;
	int Bpp;

	in_uint8(s, cache_idx);
	in_uint8(s, colour_code);
	in_uint8(s, width);
	in_uint8(s, height);
	in_uint8(s, type);	/* type, 0x8x = cached */
	in_uint8(s, size);

	DEBUG(("BRUSHCACHE(idx=%d,wd=%d,ht=%d,sz=%d)\n", cache_idx, width, height, size));

	if ((width == 8) && (height == 8))
	{
		if (colour_code == 1)
		{
			brush_data.colour_code = 1;
			brush_data.data_size = 8;
			brush_data.data = xmalloc(8);
			if (size == 8)
			{
				/* read it bottom up */
				for (index = 7; index >= 0; index--)
				{
					in_uint8(s, brush_data.data[index]);
				}
			}
			else
			{
				warning("incompatible brush, colour_code %d size %d\n", colour_code,
					size);
			}
			cache_put_brush_data(1, cache_idx, &brush_data);
		}
		else if ((colour_code >= 3) && (colour_code <= 6))
		{
			Bpp = colour_code - 2;
			brush_data.colour_code = colour_code;
			brush_data.data_size = 8 * 8 * Bpp;
			brush_data.data = xmalloc(8 * 8 * Bpp);
			if (size == 16 + 4 * Bpp)
			{
				in_uint8p(s, comp_brush, 16 + 4 * Bpp);
				process_compressed_8x8_brush_data(comp_brush, brush_data.data, Bpp);
			}
			else
			{
				in_uint8a(s, brush_data.data, 8 * 8 * Bpp);
			}
			cache_put_brush_data(colour_code, cache_idx, &brush_data);
		}
		else
		{
			warning("incompatible brush, colour_code %d size %d\n", colour_code, size);
		}
	}
	else
	{
		warning("incompatible brush, width height %d %d\n", width, height);
	}
	if (type) {}
}