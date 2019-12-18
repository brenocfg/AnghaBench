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
struct nk_color {int r; int g; int b; unsigned int a; } ;
typedef  int rawfb_pl ;

/* Variables and functions */
#define  PIXEL_LAYOUT_RGBX_8888 129 
#define  PIXEL_LAYOUT_XRGB_8888 128 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static unsigned int
nk_rawfb_color2int(const struct nk_color c, rawfb_pl pl)
{
    unsigned int res = 0;

    switch (pl) {
    case PIXEL_LAYOUT_RGBX_8888:
	res |= c.r << 24;
	res |= c.g << 16;
	res |= c.b << 8;
	res |= c.a;
	break;
    case PIXEL_LAYOUT_XRGB_8888:
	res |= c.a << 24;
	res |= c.r << 16;
	res |= c.g << 8;
	res |= c.b;
	break;

    default:
	perror("nk_rawfb_color2int(): Unsupported pixel layout.\n");
	break;
    }
    return (res);
}