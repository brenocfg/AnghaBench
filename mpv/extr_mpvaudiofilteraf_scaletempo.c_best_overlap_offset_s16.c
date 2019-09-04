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
struct priv {int* table_window; int* buf_overlap; long num_channels; int* buf_pre_corr; long samples_overlap; int frames_search; scalar_t__ buf_queue; } ;
typedef  scalar_t__ int64_t ;
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 scalar_t__ INT64_MIN ; 

__attribute__((used)) static int best_overlap_offset_s16(struct priv *s)
{
    int64_t best_corr = INT64_MIN;
    int best_off = 0;

    int32_t *pw  = s->table_window;
    int16_t *po  = s->buf_overlap;
    po += s->num_channels;
    int32_t *ppc = s->buf_pre_corr;
    for (long i = s->num_channels; i < s->samples_overlap; i++)
        *ppc++ = (*pw++ **po++) >> 15;

    int16_t *search_start = (int16_t *)s->buf_queue + s->num_channels;
    for (int off = 0; off < s->frames_search; off++) {
        int64_t corr = 0;
        int16_t *ps = search_start;
        ppc = s->buf_pre_corr;
        ppc += s->samples_overlap - s->num_channels;
        ps  += s->samples_overlap - s->num_channels;
        long i  = -(s->samples_overlap - s->num_channels);
        do {
            corr += ppc[i + 0] * ps[i + 0];
            corr += ppc[i + 1] * ps[i + 1];
            corr += ppc[i + 2] * ps[i + 2];
            corr += ppc[i + 3] * ps[i + 3];
            i += 4;
        } while (i < 0);
        if (corr > best_corr) {
            best_corr = corr;
            best_off  = off;
        }
        search_start += s->num_channels;
    }

    return best_off * 2 * s->num_channels;
}