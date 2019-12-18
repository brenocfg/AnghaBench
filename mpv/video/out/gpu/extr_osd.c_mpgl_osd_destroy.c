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
struct mpgl_osd_part {int /*<<< orphan*/  texture; } ;
struct mpgl_osd {int /*<<< orphan*/  ra; struct mpgl_osd_part** parts; } ;

/* Variables and functions */
 int MAX_OSD_PARTS ; 
 int /*<<< orphan*/  ra_tex_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct mpgl_osd*) ; 

void mpgl_osd_destroy(struct mpgl_osd *ctx)
{
    if (!ctx)
        return;

    for (int n = 0; n < MAX_OSD_PARTS; n++) {
        struct mpgl_osd_part *p = ctx->parts[n];
        ra_tex_free(ctx->ra, &p->texture);
    }
    talloc_free(ctx);
}