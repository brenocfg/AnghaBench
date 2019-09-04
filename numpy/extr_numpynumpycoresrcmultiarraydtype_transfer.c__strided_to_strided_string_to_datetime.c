#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ npy_intp ;
typedef  char npy_int64 ;
typedef  int /*<<< orphan*/  npy_datetimestruct ;
typedef  int /*<<< orphan*/  dt ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct TYPE_3__ {char* tmp_buffer; TYPE_2__ dst_meta; } ;
typedef  TYPE_1__ _strided_datetime_cast_data ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 char NPY_DATETIME_NAT ; 
 int /*<<< orphan*/  NPY_SAME_KIND_CASTING ; 
 scalar_t__ convert_datetimestruct_to_datetime (TYPE_2__*,int /*<<< orphan*/ *,char*) ; 
 char* memchr (char*,char,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ parse_iso_8601_datetime (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_strided_to_strided_string_to_datetime(char *dst, npy_intp dst_stride,
                        char *src, npy_intp src_stride,
                        npy_intp N, npy_intp src_itemsize,
                        NpyAuxData *data)
{
    _strided_datetime_cast_data *d = (_strided_datetime_cast_data *)data;
    npy_datetimestruct dts;
    char *tmp_buffer = d->tmp_buffer;
    char *tmp;

    while (N > 0) {
        npy_int64 dt = ~NPY_DATETIME_NAT;

        /* Replicating strnlen with memchr, because Mac OS X lacks it */
        tmp = memchr(src, '\0', src_itemsize);

        /* If the string is all full, use the buffer */
        if (tmp == NULL) {
            memcpy(tmp_buffer, src, src_itemsize);
            tmp_buffer[src_itemsize] = '\0';

            if (parse_iso_8601_datetime(tmp_buffer, src_itemsize,
                                    d->dst_meta.base, NPY_SAME_KIND_CASTING,
                                    &dts, NULL, NULL) < 0) {
                dt = NPY_DATETIME_NAT;
            }
        }
        /* Otherwise parse the data in place */
        else {
            if (parse_iso_8601_datetime(src, tmp - src,
                                    d->dst_meta.base, NPY_SAME_KIND_CASTING,
                                    &dts, NULL, NULL) < 0) {
                dt = NPY_DATETIME_NAT;
            }
        }

        /* Convert to the datetime */
        if (dt != NPY_DATETIME_NAT &&
                convert_datetimestruct_to_datetime(&d->dst_meta,
                                               &dts, &dt) < 0) {
            dt = NPY_DATETIME_NAT;
        }

        memcpy(dst, &dt, sizeof(dt));

        dst += dst_stride;
        src += src_stride;
        --N;
    }
}