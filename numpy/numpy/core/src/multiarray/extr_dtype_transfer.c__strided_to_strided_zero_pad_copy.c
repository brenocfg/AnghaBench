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
struct TYPE_2__ {scalar_t__ dst_itemsize; } ;
typedef  TYPE_1__ _strided_zero_pad_data ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
_strided_to_strided_zero_pad_copy(char *dst, npy_intp dst_stride,
                        char *src, npy_intp src_stride,
                        npy_intp N, npy_intp src_itemsize,
                        NpyAuxData *data)
{
    _strided_zero_pad_data *d = (_strided_zero_pad_data *)data;
    npy_intp dst_itemsize = d->dst_itemsize;
    npy_intp zero_size = dst_itemsize-src_itemsize;

    while (N > 0) {
        memcpy(dst, src, src_itemsize);
        memset(dst + src_itemsize, 0, zero_size);
        src += src_stride;
        dst += dst_stride;
        --N;
    }
}