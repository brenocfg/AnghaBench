#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
struct TYPE_9__ {int style; int* pattern; TYPE_1__* bd; } ;
struct TYPE_8__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ BRUSHDATA ;
typedef  TYPE_2__ BRUSH ;

/* Variables and functions */
 TYPE_1__* cache_get_brush_data (int,int) ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
setup_brush(BRUSH * out_brush, BRUSH * in_brush)
{
	BRUSHDATA *brush_data;
	uint8 cache_idx;
	uint8 colour_code;

	memcpy(out_brush, in_brush, sizeof(BRUSH));
	if (out_brush->style & 0x80)
	{
		colour_code = out_brush->style & 0x0f;
		cache_idx = out_brush->pattern[0];
		brush_data = cache_get_brush_data(colour_code, cache_idx);
		if ((brush_data == NULL) || (brush_data->data == NULL))
		{
			error("error getting brush data, style %x\n", out_brush->style);
			out_brush->bd = NULL;
			memset(out_brush->pattern, 0, 8);
		}
		else
		{
			out_brush->bd = brush_data;
		}
		out_brush->style = 3;
	}
}