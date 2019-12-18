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
typedef  int /*<<< orphan*/  _ufunc_masker_data ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 scalar_t__ PyArray_malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static NpyAuxData *
ufunc_masker_data_clone(NpyAuxData *data)
{
    _ufunc_masker_data *n;

    /* Allocate a new one */
    n = (_ufunc_masker_data *)PyArray_malloc(sizeof(_ufunc_masker_data));
    if (n == NULL) {
        return NULL;
    }

    /* Copy the data (unmasked data doesn't have object semantics) */
    memcpy(n, data, sizeof(_ufunc_masker_data));

    return (NpyAuxData *)n;
}