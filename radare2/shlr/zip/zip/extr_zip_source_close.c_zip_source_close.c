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
struct TYPE_2__ {int /*<<< orphan*/  (* l ) (struct zip_source*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* f ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct zip_source {scalar_t__ is_open; struct zip_source* src; int /*<<< orphan*/  ud; TYPE_1__ cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZIP_SOURCE_CLOSE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct zip_source*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
zip_source_close(struct zip_source *src)
{
    if (!src->is_open)
	return;

    if (src->src == NULL)
	(void)src->cb.f(src->ud, NULL, 0, ZIP_SOURCE_CLOSE);
    else {
	(void)src->cb.l(src->src, src->ud, NULL, 0, ZIP_SOURCE_CLOSE);
	zip_source_close(src->src);
    }
    
    src->is_open = 0;
}