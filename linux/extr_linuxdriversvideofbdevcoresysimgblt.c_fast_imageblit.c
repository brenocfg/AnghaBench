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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  line_length; } ;
struct TYPE_3__ {int bits_per_pixel; } ;
struct fb_info {TYPE_2__ fix; TYPE_1__ var; } ;
struct fb_image {int width; char* data; int height; } ;

/* Variables and functions */
 int* cfb_tab16_be ; 
 int* cfb_tab16_le ; 
 int* cfb_tab32 ; 
 int* cfb_tab8_be ; 
 int* cfb_tab8_le ; 
 int /*<<< orphan*/  fb_be_math (struct fb_info*) ; 

__attribute__((used)) static void fast_imageblit(const struct fb_image *image, struct fb_info *p,
				  void *dst1, u32 fgcolor, u32 bgcolor)
{
	u32 fgx = fgcolor, bgx = bgcolor, bpp = p->var.bits_per_pixel;
	u32 ppw = 32/bpp, spitch = (image->width + 7)/8;
	u32 bit_mask, end_mask, eorx, shift;
	const char *s = image->data, *src;
	u32 *dst;
	const u32 *tab = NULL;
	int i, j, k;

	switch (bpp) {
	case 8:
		tab = fb_be_math(p) ? cfb_tab8_be : cfb_tab8_le;
		break;
	case 16:
		tab = fb_be_math(p) ? cfb_tab16_be : cfb_tab16_le;
		break;
	case 32:
	default:
		tab = cfb_tab32;
		break;
	}

	for (i = ppw-1; i--; ) {
		fgx <<= bpp;
		bgx <<= bpp;
		fgx |= fgcolor;
		bgx |= bgcolor;
	}

	bit_mask = (1 << ppw) - 1;
	eorx = fgx ^ bgx;
	k = image->width/ppw;

	for (i = image->height; i--; ) {
		dst = dst1;
		shift = 8;
		src = s;

		for (j = k; j--; ) {
			shift -= ppw;
			end_mask = tab[(*src >> shift) & bit_mask];
			*dst++ = (end_mask & eorx) ^ bgx;
			if (!shift) {
				shift = 8;
				src++;
			}
		}
		dst1 += p->fix.line_length;
		s += spitch;
	}
}