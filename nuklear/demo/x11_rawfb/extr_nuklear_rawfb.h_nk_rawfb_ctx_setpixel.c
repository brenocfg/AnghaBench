#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {short const h; short const y; short const x; short const w; } ;
struct TYPE_4__ {unsigned char* pixels; short const pitch; int /*<<< orphan*/  pl; } ;
struct rawfb_context {TYPE_1__ scissors; TYPE_2__ fb; } ;
struct nk_color {int dummy; } ;

/* Variables and functions */
 unsigned int nk_rawfb_color2int (struct nk_color const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nk_rawfb_ctx_setpixel(const struct rawfb_context *rawfb,
    const short x0, const short y0, const struct nk_color col)
{
    unsigned int c = nk_rawfb_color2int(col, rawfb->fb.pl);
    unsigned char *pixels = rawfb->fb.pixels;
    unsigned int *ptr;

    pixels += y0 * rawfb->fb.pitch;
    ptr = (unsigned int *)pixels + x0;

    if (y0 < rawfb->scissors.h && y0 >= rawfb->scissors.y &&
        x0 >= rawfb->scissors.x && x0 < rawfb->scissors.w)
        *ptr = c;
}