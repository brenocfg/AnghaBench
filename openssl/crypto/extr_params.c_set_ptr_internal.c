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
struct TYPE_3__ {size_t return_size; unsigned int data_type; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ OSSL_PARAM ;

/* Variables and functions */

__attribute__((used)) static int set_ptr_internal(OSSL_PARAM *p, const void *val,
                            unsigned int type, size_t len)
{
    p->return_size = len;
    if (p->data_type != type)
        return 0;
    if (p->data != NULL)
        *(const void **)p->data = val;
    return 1;
}