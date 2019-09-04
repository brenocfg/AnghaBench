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
 int /*<<< orphan*/  imgfmt2pixfmt (int) ; 
 int mp_imgfmt_select_best (int,int,int) ; 
 int sws_isSupportedInput (int /*<<< orphan*/ ) ; 
 int sws_isSupportedOutput (int /*<<< orphan*/ ) ; 

int mp_sws_find_best_out_format(int in_format, int *out_formats,
                                int num_out_formats)
{
    if (sws_isSupportedInput(imgfmt2pixfmt(in_format)) < 1)
        return 0;

    int best = 0;
    for (int n = 0; n < num_out_formats; n++) {
        int out_format = out_formats[n];

        if (sws_isSupportedOutput(imgfmt2pixfmt(out_format)) < 1)
            continue;

        if (best) {
            int candidate = mp_imgfmt_select_best(best, out_format, in_format);
            if (candidate)
                best = candidate;
        } else {
            best = out_format;
        }
    }
    return best;
}