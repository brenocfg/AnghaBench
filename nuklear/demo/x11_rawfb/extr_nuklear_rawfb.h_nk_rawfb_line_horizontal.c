#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char* pixels; short const pitch; int /*<<< orphan*/  pl; } ;
struct rawfb_context {TYPE_1__ fb; } ;
struct nk_color {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,unsigned int*,int) ; 
 unsigned int nk_rawfb_color2int (struct nk_color const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nk_rawfb_line_horizontal(const struct rawfb_context *rawfb,
    const short x0, const short y, const short x1, const struct nk_color col)
{
    /* This function is called the most. Try to optimize it a bit...
     * It does not check for scissors or image borders.
     * The caller has to make sure it does no exceed bounds. */
    unsigned int i, n;
    unsigned int c[16];
    unsigned char *pixels = rawfb->fb.pixels;
    unsigned int *ptr;

    pixels += y * rawfb->fb.pitch;
    ptr = (unsigned int *)pixels + x0;

    n = x1 - x0;
    for (i = 0; i < sizeof(c) / sizeof(c[0]); i++)
        c[i] = nk_rawfb_color2int(col, rawfb->fb.pl);

    while (n > 16) {
        memcpy((void *)ptr, c, sizeof(c));
        n -= 16; ptr += 16;
    } for (i = 0; i < n; i++)
        ptr[i] = c[i];
}