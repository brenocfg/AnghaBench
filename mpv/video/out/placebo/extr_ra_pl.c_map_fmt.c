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
struct ra_format {struct pl_fmt const* priv; } ;
struct ra {int num_formats; struct ra_format** formats; } ;
struct pl_fmt {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct ra*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ra_format *map_fmt(struct ra *ra, const struct pl_fmt *plfmt)
{
    for (int i = 0; i < ra->num_formats; i++) {
        if (ra->formats[i]->priv == plfmt)
            return ra->formats[i];
    }

    MP_ERR(ra, "Failed mapping pl_fmt '%s' to ra_fmt?\n", plfmt->name);
    return NULL;
}