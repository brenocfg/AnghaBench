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
struct rawfb_context {int dummy; } ;
struct nk_vec2i {float x; float y; } ;
struct nk_color {int dummy; } ;

/* Variables and functions */
 unsigned int MAX (unsigned int const,int) ; 
 int /*<<< orphan*/  nk_rawfb_stroke_line (struct rawfb_context const*,float,float,short,short,unsigned short const,struct nk_color const) ; 

__attribute__((used)) static void
nk_rawfb_stroke_curve(const struct rawfb_context *rawfb,
    const struct nk_vec2i p1, const struct nk_vec2i p2,
    const struct nk_vec2i p3, const struct nk_vec2i p4,
    const unsigned int num_segments, const unsigned short line_thickness,
    const struct nk_color col)
{
    unsigned int i_step, segments;
    float t_step;
    struct nk_vec2i last = p1;

    segments = MAX(num_segments, 1);
    t_step = 1.0f/(float)segments;
    for (i_step = 1; i_step <= segments; ++i_step) {
        float t = t_step * (float)i_step;
        float u = 1.0f - t;
        float w1 = u*u*u;
        float w2 = 3*u*u*t;
        float w3 = 3*u*t*t;
        float w4 = t * t *t;
        float x = w1 * p1.x + w2 * p2.x + w3 * p3.x + w4 * p4.x;
        float y = w1 * p1.y + w2 * p2.y + w3 * p3.y + w4 * p4.y;
        nk_rawfb_stroke_line(rawfb, last.x, last.y,
                (short)x, (short)y, line_thickness,col);
        last.x = (short)x; last.y = (short)y;
    }
}