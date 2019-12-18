#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int npy_intp ;
struct TYPE_4__ {int src_itemsize; int dst_itemsize; char* bufferin; char* bufferout; int /*<<< orphan*/ * todata; int /*<<< orphan*/ * wrappeddata; int /*<<< orphan*/ * fromdata; } ;
typedef  TYPE_1__ _align_wrap_data ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 void* NPY_AUXDATA_CLONE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NPY_AUXDATA_FREE (int /*<<< orphan*/ *) ; 
 int NPY_LOWLEVEL_BUFFER_BLOCKSIZE ; 
 int /*<<< orphan*/  PyArray_free (TYPE_1__*) ; 
 scalar_t__ PyArray_malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static NpyAuxData *_align_wrap_data_clone(NpyAuxData *data)
{
    _align_wrap_data *d = (_align_wrap_data *)data;
    _align_wrap_data *newdata;
    npy_intp basedatasize, datasize;

    /* Round up the structure size to 16-byte boundary */
    basedatasize = (sizeof(_align_wrap_data)+15)&(-0x10);
    /* Add space for two low level buffers */
    datasize = basedatasize +
                NPY_LOWLEVEL_BUFFER_BLOCKSIZE*d->src_itemsize +
                NPY_LOWLEVEL_BUFFER_BLOCKSIZE*d->dst_itemsize;

    /* Allocate the data, and populate it */
    newdata = (_align_wrap_data *)PyArray_malloc(datasize);
    if (newdata == NULL) {
        return NULL;
    }
    memcpy(newdata, data, basedatasize);
    newdata->bufferin = (char *)newdata + basedatasize;
    newdata->bufferout = newdata->bufferin +
                NPY_LOWLEVEL_BUFFER_BLOCKSIZE*newdata->src_itemsize;
    if (newdata->wrappeddata != NULL) {
        newdata->wrappeddata = NPY_AUXDATA_CLONE(d->wrappeddata);
        if (newdata->wrappeddata == NULL) {
            PyArray_free(newdata);
            return NULL;
        }
    }
    if (newdata->todata != NULL) {
        newdata->todata = NPY_AUXDATA_CLONE(d->todata);
        if (newdata->todata == NULL) {
            NPY_AUXDATA_FREE(newdata->wrappeddata);
            PyArray_free(newdata);
            return NULL;
        }
    }
    if (newdata->fromdata != NULL) {
        newdata->fromdata = NPY_AUXDATA_CLONE(d->fromdata);
        if (newdata->fromdata == NULL) {
            NPY_AUXDATA_FREE(newdata->wrappeddata);
            NPY_AUXDATA_FREE(newdata->todata);
            PyArray_free(newdata);
            return NULL;
        }
    }

    return (NpyAuxData *)newdata;
}