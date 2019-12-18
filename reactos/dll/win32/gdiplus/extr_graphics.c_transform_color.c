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
typedef  int ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  max (int,int /*<<< orphan*/ ) ; 
 unsigned char min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ARGB transform_color(ARGB color, int matrix[5][5])
{
    int val[5], res[4];
    int i, j;
    unsigned char a, r, g, b;

    val[0] = ((color >> 16) & 0xff); /* red */
    val[1] = ((color >> 8) & 0xff); /* green */
    val[2] = (color & 0xff); /* blue */
    val[3] = ((color >> 24) & 0xff); /* alpha */
    val[4] = 255; /* translation */

    for (i=0; i<4; i++)
    {
        res[i] = 0;

        for (j=0; j<5; j++)
            res[i] += matrix[j][i] * val[j];
    }

    a = min(max(res[3] / 256, 0), 255);
    r = min(max(res[0] / 256, 0), 255);
    g = min(max(res[1] / 256, 0), 255);
    b = min(max(res[2] / 256, 0), 255);

    return (a << 24) | (r << 16) | (g << 8) | b;
}