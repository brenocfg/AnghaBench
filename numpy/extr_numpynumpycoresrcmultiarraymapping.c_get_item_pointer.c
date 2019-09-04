#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int value; } ;
typedef  TYPE_1__ npy_index_info ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 char* PyArray_BYTES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_DIMS (int /*<<< orphan*/ *) ; 
 int PyArray_STRIDE (int /*<<< orphan*/ *,int) ; 
 scalar_t__ check_and_adjust_index (int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_item_pointer(PyArrayObject *self, char **ptr,
                    npy_index_info *indices, int index_num) {
    int i;
    *ptr = PyArray_BYTES(self);
    for (i=0; i < index_num; i++) {
        if ((check_and_adjust_index(&(indices[i].value),
                               PyArray_DIMS(self)[i], i, NULL)) < 0) {
            return -1;
        }
        *ptr += PyArray_STRIDE(self, i) * indices[i].value;
    }
    return 0;
}