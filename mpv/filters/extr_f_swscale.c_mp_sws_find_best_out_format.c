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
struct mp_sws_filter {int /*<<< orphan*/  sws; } ;

/* Variables and functions */
 int mp_imgfmt_select_best (int,int,int) ; 
 int /*<<< orphan*/  mp_sws_supports_formats (int /*<<< orphan*/ ,int,int) ; 

int mp_sws_find_best_out_format(struct mp_sws_filter *sws, int in_format,
                                int *out_formats, int num_out_formats)
{
    int best = 0;
    for (int n = 0; n < num_out_formats; n++) {
        int out_format = out_formats[n];

        if (!mp_sws_supports_formats(sws->sws, out_format, in_format))
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