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
typedef  float REAL ;
typedef  int INT ;
typedef  int ARGB ;

/* Variables and functions */

__attribute__((used)) static ARGB blend_colors(ARGB start, ARGB end, REAL position)
{
    INT start_a, end_a, final_a;
    INT pos;

    pos = (INT)(position * 255.0f + 0.5f);

    start_a = ((start >> 24) & 0xff) * (pos ^ 0xff);
    end_a = ((end >> 24) & 0xff) * pos;

    final_a = start_a + end_a;

    if (final_a < 0xff) return 0;

    return (final_a / 0xff) << 24 |
        ((((start >> 16) & 0xff) * start_a + (((end >> 16) & 0xff) * end_a)) / final_a) << 16 |
        ((((start >> 8) & 0xff) * start_a + (((end >> 8) & 0xff) * end_a)) / final_a) << 8 |
        (((start & 0xff) * start_a + ((end & 0xff) * end_a)) / final_a);
}