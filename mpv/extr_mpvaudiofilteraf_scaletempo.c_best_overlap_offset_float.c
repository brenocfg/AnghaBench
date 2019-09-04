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
struct priv {float* table_window; float* buf_overlap; int num_channels; float* buf_pre_corr; int samples_overlap; int frames_search; scalar_t__ buf_queue; } ;

/* Variables and functions */
 float INT_MIN ; 

__attribute__((used)) static int best_overlap_offset_float(struct priv *s)
{
    float best_corr = INT_MIN;
    int best_off = 0;

    float *pw  = s->table_window;
    float *po  = s->buf_overlap;
    po += s->num_channels;
    float *ppc = s->buf_pre_corr;
    for (int i = s->num_channels; i < s->samples_overlap; i++)
        *ppc++ = *pw++ **po++;

    float *search_start = (float *)s->buf_queue + s->num_channels;
    for (int off = 0; off < s->frames_search; off++) {
        float corr = 0;
        float *ps = search_start;
        ppc = s->buf_pre_corr;
        for (int i = s->num_channels; i < s->samples_overlap; i++)
            corr += *ppc++ **ps++;
        if (corr > best_corr) {
            best_corr = corr;
            best_off  = off;
        }
        search_start += s->num_channels;
    }

    return best_off * 4 * s->num_channels;
}