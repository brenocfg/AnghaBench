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
typedef  scalar_t__ zip_int64_t ;
struct TYPE_2__ {scalar_t__ (* f ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* l ) (struct zip_source*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct zip_source {int is_open; void* error_source; struct zip_source* src; int /*<<< orphan*/  ud; TYPE_1__ cb; } ;

/* Variables and functions */
 void* ZIP_LES_INVAL ; 
 void* ZIP_LES_LOWER ; 
 void* ZIP_LES_UPPER ; 
 scalar_t__ ZIP_SOURCE_ERR_LOWER ; 
 int /*<<< orphan*/  ZIP_SOURCE_OPEN ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct zip_source*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zip_source_close (struct zip_source*) ; 

int
zip_source_open(struct zip_source *src)
{
    zip_int64_t ret;

    if (src->is_open) {
	src->error_source = ZIP_LES_INVAL;
	return -1;
    }

    if (src->src == NULL) {
	if (src->cb.f(src->ud, NULL, 0, ZIP_SOURCE_OPEN) < 0)
	    return -1;
    }
    else {
	if (zip_source_open(src->src) < 0) {
	    src->error_source = ZIP_LES_LOWER;
	    return -1;
	}

	ret = src->cb.l(src->src, src->ud, NULL, 0, ZIP_SOURCE_OPEN);
	
	if (ret < 0) {
	    zip_source_close(src->src);
	    
	    if (ret == ZIP_SOURCE_ERR_LOWER)
		src->error_source = ZIP_LES_LOWER;
	    else
		src->error_source = ZIP_LES_UPPER;
	    return -1;
	}
    }

    src->is_open = 1;
    
    return 0;
}