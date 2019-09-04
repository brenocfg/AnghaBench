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
typedef  int u8 ;
typedef  size_t u32 ;
struct ssd1307fb_par {int width; int height; int /*<<< orphan*/  client; TYPE_1__* info; } ;
struct ssd1307fb_array {int* data; } ;
struct TYPE_2__ {int* screen_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSD1307FB_DATA ; 
 int /*<<< orphan*/  kfree (struct ssd1307fb_array*) ; 
 struct ssd1307fb_array* ssd1307fb_alloc_array (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssd1307fb_write_array (int /*<<< orphan*/ ,struct ssd1307fb_array*,int) ; 

__attribute__((used)) static void ssd1307fb_update_display(struct ssd1307fb_par *par)
{
	struct ssd1307fb_array *array;
	u8 *vmem = par->info->screen_base;
	int i, j, k;

	array = ssd1307fb_alloc_array(par->width * par->height / 8,
				      SSD1307FB_DATA);
	if (!array)
		return;

	/*
	 * The screen is divided in pages, each having a height of 8
	 * pixels, and the width of the screen. When sending a byte of
	 * data to the controller, it gives the 8 bits for the current
	 * column. I.e, the first byte are the 8 bits of the first
	 * column, then the 8 bits for the second column, etc.
	 *
	 *
	 * Representation of the screen, assuming it is 5 bits
	 * wide. Each letter-number combination is a bit that controls
	 * one pixel.
	 *
	 * A0 A1 A2 A3 A4
	 * B0 B1 B2 B3 B4
	 * C0 C1 C2 C3 C4
	 * D0 D1 D2 D3 D4
	 * E0 E1 E2 E3 E4
	 * F0 F1 F2 F3 F4
	 * G0 G1 G2 G3 G4
	 * H0 H1 H2 H3 H4
	 *
	 * If you want to update this screen, you need to send 5 bytes:
	 *  (1) A0 B0 C0 D0 E0 F0 G0 H0
	 *  (2) A1 B1 C1 D1 E1 F1 G1 H1
	 *  (3) A2 B2 C2 D2 E2 F2 G2 H2
	 *  (4) A3 B3 C3 D3 E3 F3 G3 H3
	 *  (5) A4 B4 C4 D4 E4 F4 G4 H4
	 */

	for (i = 0; i < (par->height / 8); i++) {
		for (j = 0; j < par->width; j++) {
			u32 array_idx = i * par->width + j;
			array->data[array_idx] = 0;
			for (k = 0; k < 8; k++) {
				u32 page_length = par->width * i;
				u32 index = page_length + (par->width * k + j) / 8;
				u8 byte = *(vmem + index);
				u8 bit = byte & (1 << (j % 8));
				bit = bit >> (j % 8);
				array->data[array_idx] |= bit << k;
			}
		}
	}

	ssd1307fb_write_array(par->client, array, par->width * par->height / 8);
	kfree(array);
}