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
struct image {int padding; int /*<<< orphan*/  transform; int /*<<< orphan*/  multiplier; } ;
struct gl_video {int dummy; } ;
typedef  int /*<<< orphan*/  crap ;

/* Variables and functions */
 int /*<<< orphan*/  GLSLHF (char*,char const*,...) ; 
 char* get_tex_swizzle (struct image*) ; 
 scalar_t__ gl_transform_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  identity_trans ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void hook_prelude(struct gl_video *p, const char *name, int id,
                         struct image img)
{
    GLSLHF("#define %s_raw texture%d\n", name, id);
    GLSLHF("#define %s_pos texcoord%d\n", name, id);
    GLSLHF("#define %s_size texture_size%d\n", name, id);
    GLSLHF("#define %s_rot texture_rot%d\n", name, id);
    GLSLHF("#define %s_off texture_off%d\n", name, id);
    GLSLHF("#define %s_pt pixel_size%d\n", name, id);
    GLSLHF("#define %s_map texmap%d\n", name, id);
    GLSLHF("#define %s_mul %f\n", name, img.multiplier);

    char crap[5] = "";
    snprintf(crap, sizeof(crap), "%s", get_tex_swizzle(&img));

    // Remove leading padding by rotating the swizzle mask.
    int len = strlen(crap);
    for (int n = 0; n < img.padding; n++) {
        if (len) {
            char f = crap[0];
            memmove(crap, crap + 1, len - 1);
            crap[len - 1] = f;
        }
    }

    // Set up the sampling functions
    GLSLHF("#define %s_tex(pos) (%s_mul * vec4(texture(%s_raw, pos)).%s)\n",
           name, name, name, crap);

    // Since the extra matrix multiplication impacts performance,
    // skip it unless the texture was actually rotated
    if (gl_transform_eq(img.transform, identity_trans)) {
        GLSLHF("#define %s_texOff(off) %s_tex(%s_pos + %s_pt * vec2(off))\n",
               name, name, name, name);
    } else {
        GLSLHF("#define %s_texOff(off) "
                   "%s_tex(%s_pos + %s_rot * vec2(off)/%s_size)\n",
               name, name, name, name, name);
    }
}