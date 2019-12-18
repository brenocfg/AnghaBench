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
struct TYPE_4__ {scalar_t__ ndim; scalar_t__* shape; scalar_t__* strides; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ _buffer_info_t ;
typedef  scalar_t__ Py_ssize_t ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Py_ssize_t
_buffer_info_cmp(_buffer_info_t *a, _buffer_info_t *b)
{
    Py_ssize_t c;
    int k;

    c = strcmp(a->format, b->format);
    if (c != 0) return c;

    c = a->ndim - b->ndim;
    if (c != 0) return c;

    for (k = 0; k < a->ndim; ++k) {
        c = a->shape[k] - b->shape[k];
        if (c != 0) return c;
        c = a->strides[k] - b->strides[k];
        if (c != 0) return c;
    }

    return 0;
}