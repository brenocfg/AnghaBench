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
struct TYPE_4__ {unsigned int data_type; scalar_t__ data; } ;
typedef  TYPE_1__ OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  SET_RETURN_SIZE (TYPE_1__ const*,size_t) ; 

__attribute__((used)) static int set_ptr_internal(const OSSL_PARAM *p, const void *val,
                            unsigned int type, size_t len)
{
    SET_RETURN_SIZE(p, len);
    if (p->data_type != type)
        return 0;
    *(const void **)p->data = val;
    return 1;
}