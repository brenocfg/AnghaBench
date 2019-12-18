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
typedef  scalar_t__ zip_uint64_t ;
typedef  int zip_int64_t ;
struct TYPE_2__ {int (* f ) (int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ ) ;int (* l ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct zip_source {int /*<<< orphan*/  error_source; int /*<<< orphan*/  ud; int /*<<< orphan*/ * src; TYPE_1__ cb; int /*<<< orphan*/  is_open; } ;

/* Variables and functions */
 scalar_t__ ZIP_INT64_MAX ; 
 int /*<<< orphan*/  ZIP_LES_INVAL ; 
 int /*<<< orphan*/  ZIP_LES_LOWER ; 
 int /*<<< orphan*/  ZIP_LES_UPPER ; 
 int ZIP_SOURCE_ERR_LOWER ; 
 int /*<<< orphan*/  ZIP_SOURCE_READ ; 
 int stub1 (int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ ) ; 

zip_int64_t
zip_source_read(struct zip_source *src, void *data, zip_uint64_t len)
{
    zip_int64_t ret;

    if (!src->is_open || len > ZIP_INT64_MAX || (len > 0 && data == NULL)) {
	src->error_source = ZIP_LES_INVAL;
	return -1;
    }

    if (src->src == NULL)
	return src->cb.f(src->ud, data, len, ZIP_SOURCE_READ);

    ret = src->cb.l(src->src, src->ud, data, len, ZIP_SOURCE_READ);

    if (ret < 0) {
	if (ret == ZIP_SOURCE_ERR_LOWER)
	    src->error_source = ZIP_LES_LOWER;
	else
	    src->error_source = ZIP_LES_UPPER;
	return -1;
    }
    
    return ret;
}