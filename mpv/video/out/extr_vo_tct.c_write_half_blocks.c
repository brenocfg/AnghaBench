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

/* Variables and functions */
 char* ESC_CLEAR_COLORS ; 
 char* ESC_COLOR256_BG ; 
 char* ESC_COLOR256_FG ; 
 char* ESC_COLOR_BG ; 
 char* ESC_COLOR_FG ; 
 char* ESC_GOTOXY ; 
 int /*<<< orphan*/  assert (unsigned char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rgb_to_x256 (unsigned char,unsigned char,unsigned char) ; 

__attribute__((used)) static void write_half_blocks(
    const int dwidth, const int dheight,
    const int swidth, const int sheight,
    unsigned char *source, int source_stride,
    bool term256)
{
    assert(source);
    const int tx = (dwidth - swidth) / 2;
    const int ty = (dheight - sheight) / 2;
    for (int y = 0; y < sheight * 2; y += 2) {
        const unsigned char *row_up = source + y * source_stride;
        const unsigned char *row_down = source + (y + 1) * source_stride;
        printf(ESC_GOTOXY, ty + y / 2, tx);
        for (int x = 0; x < swidth; x++) {
            unsigned char b_up = *row_up++;
            unsigned char g_up = *row_up++;
            unsigned char r_up = *row_up++;
            unsigned char b_down = *row_down++;
            unsigned char g_down = *row_down++;
            unsigned char r_down = *row_down++;
            if (term256) {
                printf(ESC_COLOR256_BG, rgb_to_x256(r_up, g_up, b_up));
                printf(ESC_COLOR256_FG, rgb_to_x256(r_down, g_down, b_down));
            } else {
                printf(ESC_COLOR_BG, r_up, g_up, b_up);
                printf(ESC_COLOR_FG, r_down, g_down, b_down);
            }
            printf("\xe2\x96\x84");  // UTF8 bytes of U+2584 (lower half block)
        }
        printf(ESC_CLEAR_COLORS);
    }
    printf("\n");
}