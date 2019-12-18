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
struct mp_cmat {double* c; int** m; } ;

/* Variables and functions */
 int av_clip (int,int /*<<< orphan*/ ,int) ; 
 int lrint (double) ; 

void mp_map_fixp_color(struct mp_cmat *matrix, int ibits, int in[3],
                                               int obits, int out[3])
{
    for (int i = 0; i < 3; i++) {
        double val = matrix->c[i];
        for (int x = 0; x < 3; x++)
            val += matrix->m[i][x] * in[x] / ((1 << ibits) - 1);
        int ival = lrint(val * ((1 << obits) - 1));
        out[i] = av_clip(ival, 0, (1 << obits) - 1);
    }
}