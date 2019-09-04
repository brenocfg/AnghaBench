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
 char* ESC_COLOR_BG ; 
 char* ESC_GOTOXY ; 
 int /*<<< orphan*/  assert (unsigned char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rgb_to_x256 (unsigned char,unsigned char,unsigned char) ; 

__attribute__((used)) static void write_plain(
    const int dwidth, const int dheight,
    const int swidth, const int sheight,
    const unsigned char *source, const int source_stride,
    bool term256)
{
    assert(source);
    const int tx = (dwidth - swidth) / 2;
    const int ty = (dheight - sheight) / 2;
    for (int y = 0; y < sheight; y++) {
        const unsigned char *row = source + y * source_stride;
        printf(ESC_GOTOXY, ty + y, tx);
        for (int x = 0; x < swidth; x++) {
            unsigned char b = *row++;
            unsigned char g = *row++;
            unsigned char r = *row++;
            if (term256) {
                printf(ESC_COLOR256_BG, rgb_to_x256(r, g, b));
            } else {
                printf(ESC_COLOR_BG, r, g, b);
            }
            printf(" ");
        }
        printf(ESC_CLEAR_COLORS);
    }
    printf("\n");
}