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
struct ra_hwdec_mapper {int /*<<< orphan*/  ra; } ;
struct queue_surf {int /*<<< orphan*/  tex; int /*<<< orphan*/  stage9; int /*<<< orphan*/  surf9; int /*<<< orphan*/  tex9; int /*<<< orphan*/  stage11; int /*<<< orphan*/  idle11; int /*<<< orphan*/  tex11; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAFE_RELEASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_tex_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct queue_surf*) ; 

__attribute__((used)) static void surf_destroy(struct ra_hwdec_mapper *mapper,
                         struct queue_surf *surf)
{
    if (!surf)
        return;
    SAFE_RELEASE(surf->tex11);
    SAFE_RELEASE(surf->idle11);
    SAFE_RELEASE(surf->stage11);
    SAFE_RELEASE(surf->tex9);
    SAFE_RELEASE(surf->surf9);
    SAFE_RELEASE(surf->stage9);
    ra_tex_free(mapper->ra, &surf->tex);
    talloc_free(surf);
}