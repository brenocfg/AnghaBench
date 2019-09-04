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
struct TYPE_3__ {scalar_t__ data_type; int data_size; scalar_t__ data; } ;
typedef  TYPE_1__ OSSL_PARAM ;

/* Variables and functions */
 scalar_t__ OSSL_PARAM_REAL ; 

int OSSL_PARAM_get_double(const OSSL_PARAM *p, double *val)
{
    if (val == NULL || p == NULL || p->data_type != OSSL_PARAM_REAL)
        return 0;

    switch (p->data_size) {
    case sizeof(double):
        *val = *(const double *)p->data;
        return 1;
    }
    return 0;
}