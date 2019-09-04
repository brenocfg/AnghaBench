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
struct gl_shader_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLSLF (char*,char const*,char const*,...) ; 

__attribute__((used)) static void bicubic_calcweights(struct gl_shader_cache *sc, const char *t, const char *s)
{
    // Explanation of how bicubic scaling with only 4 texel fetches is done:
    //   http://www.mate.tue.nl/mate/pdfs/10318.pdf
    //   'Efficient GPU-Based Texture Interpolation using Uniform B-Splines'
    // Explanation why this algorithm normally always blurs, even with unit
    // scaling:
    //   http://bigwww.epfl.ch/preprints/ruijters1001p.pdf
    //   'GPU Prefilter for Accurate Cubic B-spline Interpolation'
    GLSLF("vec4 %s = vec4(-0.5, 0.1666, 0.3333, -0.3333) * %s"
                " + vec4(1, 0, -0.5, 0.5);\n", t, s);
    GLSLF("%s = %s * %s + vec4(0, 0, -0.5, 0.5);\n", t, t, s);
    GLSLF("%s = %s * %s + vec4(-0.6666, 0, 0.8333, 0.1666);\n", t, t, s);
    GLSLF("%s.xy *= vec2(1, 1) / vec2(%s.z, %s.w);\n", t, t, t);
    GLSLF("%s.xy += vec2(1.0 + %s, 1.0 - %s);\n", t, s, s);
}