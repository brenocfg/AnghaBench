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
typedef  scalar_t__ npy_intp ;
typedef  char npy_int64 ;
typedef  int /*<<< orphan*/  npy_datetimestruct ;
typedef  int /*<<< orphan*/  dt ;
struct TYPE_2__ {int /*<<< orphan*/  dst_meta; int /*<<< orphan*/  src_meta; } ;
typedef  TYPE_1__ _strided_datetime_cast_data ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 char NPY_DATETIME_NAT ; 
 scalar_t__ convert_datetime_to_datetimestruct (int /*<<< orphan*/ *,char,int /*<<< orphan*/ *) ; 
 scalar_t__ convert_datetimestruct_to_datetime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static void
_strided_to_strided_datetime_general_cast(char *dst, npy_intp dst_stride,
                        char *src, npy_intp src_stride,
                        npy_intp N, npy_intp src_itemsize,
                        NpyAuxData *data)
{
    _strided_datetime_cast_data *d = (_strided_datetime_cast_data *)data;
    npy_int64 dt;
    npy_datetimestruct dts;

    while (N > 0) {
        memcpy(&dt, src, sizeof(dt));

        if (convert_datetime_to_datetimestruct(&d->src_meta,
                                               dt, &dts) < 0) {
            dt = NPY_DATETIME_NAT;
        }
        else {
            if (convert_datetimestruct_to_datetime(&d->dst_meta,
                                                   &dts, &dt) < 0) {
                dt = NPY_DATETIME_NAT;
            }
        }

        memcpy(dst, &dt, sizeof(dt));

        dst += dst_stride;
        src += src_stride;
        --N;
    }
}