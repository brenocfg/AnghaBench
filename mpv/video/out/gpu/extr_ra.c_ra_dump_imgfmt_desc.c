#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ra_imgfmt_desc {int num_planes; size_t** components; int /*<<< orphan*/  component_pad; int /*<<< orphan*/  component_bits; int /*<<< orphan*/  chroma_h; int /*<<< orphan*/  chroma_w; TYPE_1__** planes; } ;
struct ra {int dummy; } ;
typedef  int /*<<< orphan*/  pl ;
typedef  int /*<<< orphan*/  pf ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_MSG (struct ra*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  mp_snprintf_cat (char*,int,char*,...) ; 

void ra_dump_imgfmt_desc(struct ra *ra, const struct ra_imgfmt_desc *desc,
                         int msgl)
{
    char pl[80] = "";
    char pf[80] = "";
    for (int n = 0; n < desc->num_planes; n++) {
        if (n > 0) {
            mp_snprintf_cat(pl, sizeof(pl), "/");
            mp_snprintf_cat(pf, sizeof(pf), "/");
        }
        char t[5] = {0};
        for (int i = 0; i < 4; i++)
            t[i] = "_rgba"[desc->components[n][i]];
        for (int i = 3; i > 0 && t[i] == '_'; i--)
            t[i] = '\0';
        mp_snprintf_cat(pl, sizeof(pl), "%s", t);
        mp_snprintf_cat(pf, sizeof(pf), "%s", desc->planes[n]->name);
    }
    MP_MSG(ra, msgl, "%d planes %dx%d %d/%d [%s] (%s)\n",
           desc->num_planes, desc->chroma_w, desc->chroma_h,
           desc->component_bits, desc->component_pad, pf, pl);
}