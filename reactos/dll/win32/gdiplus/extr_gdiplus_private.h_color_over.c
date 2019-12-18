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
typedef  int BYTE ;
typedef  int ARGB ;

/* Variables and functions */

__attribute__((used)) static inline ARGB color_over(ARGB bg, ARGB fg)
{
    BYTE b, g, r, a;
    BYTE bg_alpha, fg_alpha;

    fg_alpha = (fg>>24)&0xff;

    if (fg_alpha == 0xff) return fg;

    if (fg_alpha == 0) return bg;

    bg_alpha = (((bg>>24)&0xff) * (0xff-fg_alpha)) / 0xff;

    if (bg_alpha == 0) return fg;

    a = bg_alpha + fg_alpha;
    b = ((bg&0xff)*bg_alpha + (fg&0xff)*fg_alpha)/a;
    g = (((bg>>8)&0xff)*bg_alpha + ((fg>>8)&0xff)*fg_alpha)/a;
    r = (((bg>>16)&0xff)*bg_alpha + ((fg>>16)&0xff)*fg_alpha)/a;

    return (a<<24)|(r<<16)|(g<<8)|b;
}