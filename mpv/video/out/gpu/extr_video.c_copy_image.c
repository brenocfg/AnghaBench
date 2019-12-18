#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct image {int components; int padding; double multiplier; TYPE_3__* tex; } ;
struct TYPE_8__ {unsigned long long component_bits; } ;
struct gl_video {TYPE_4__ ra_format; } ;
struct TYPE_6__ {TYPE_1__* format; } ;
struct TYPE_7__ {TYPE_2__ params; } ;
struct TYPE_5__ {scalar_t__ ctype; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLSLF (char*,char*,double,int,int,char*) ; 
 scalar_t__ RA_CTYPE_UINT ; 
 int /*<<< orphan*/  assert (int) ; 
 char* get_tex_swizzle (struct image*) ; 
 int pass_bind (struct gl_video*,struct image) ; 

__attribute__((used)) static void copy_image(struct gl_video *p, int *offset, struct image img)
{
    int count = img.components;
    assert(*offset + count <= 4);
    assert(img.padding + count <= 4);

    int id = pass_bind(p, img);
    char src[5] = {0};
    char dst[5] = {0};
    const char *tex_fmt = get_tex_swizzle(&img);
    const char *dst_fmt = "rgba";
    for (int i = 0; i < count; i++) {
        src[i] = tex_fmt[img.padding + i];
        dst[i] = dst_fmt[*offset + i];
    }

    if (img.tex && img.tex->params.format->ctype == RA_CTYPE_UINT) {
        uint64_t tex_max = 1ull << p->ra_format.component_bits;
        img.multiplier *= 1.0 / (tex_max - 1);
    }

    GLSLF("color.%s = %f * vec4(texture(texture%d, texcoord%d)).%s;\n",
          dst, img.multiplier, id, id, src);

    *offset += count;
}