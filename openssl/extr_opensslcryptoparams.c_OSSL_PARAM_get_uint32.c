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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ data_type; int data_size; scalar_t__ data; } ;
typedef  TYPE_1__ OSSL_PARAM ;

/* Variables and functions */
 scalar_t__ OSSL_PARAM_UNSIGNED_INTEGER ; 

int OSSL_PARAM_get_uint32(const OSSL_PARAM *p, uint32_t *val)
{
    if (val == NULL
        || p == NULL
        || (p->data_type != OSSL_PARAM_UNSIGNED_INTEGER))
        return 0;

    if (p->data_size == sizeof(uint32_t)) {
        *val = *(const uint32_t *)p->data;
        return 1;
    }
    return 0;
}