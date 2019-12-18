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
struct nk_color {unsigned int r; unsigned int g; unsigned int b; unsigned int a; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int rawfb_pl ;

/* Variables and functions */
#define  PIXEL_LAYOUT_RGBX_8888 129 
#define  PIXEL_LAYOUT_XRGB_8888 128 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static struct nk_color
nk_rawfb_int2color(const unsigned int i, rawfb_pl pl)
{
    struct nk_color col = {0,0,0,0};

    switch (pl) {
    case PIXEL_LAYOUT_RGBX_8888:
	col.r = (i >> 24) & 0xff;
	col.g = (i >> 16) & 0xff;
	col.b = (i >> 8) & 0xff;
	col.a = i & 0xff;
	break;
    case PIXEL_LAYOUT_XRGB_8888:
	col.a = (i >> 24) & 0xff;
	col.r = (i >> 16) & 0xff;
	col.g = (i >> 8) & 0xff;
	col.b = i & 0xff;
	break;

    default:
	perror("nk_rawfb_int2color(): Unsupported pixel layout.\n");
	break;
    }
    return col;
}