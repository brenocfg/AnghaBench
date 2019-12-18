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
typedef  int uint64_t ;
typedef  double uint32_t ;
typedef  int int64_t ;
typedef  double int32_t ;
struct TYPE_3__ {scalar_t__ data_type; int data_size; scalar_t__ data; } ;
typedef  TYPE_1__ OSSL_PARAM ;

/* Variables and functions */
 scalar_t__ OSSL_PARAM_INTEGER ; 
 scalar_t__ OSSL_PARAM_REAL ; 
 scalar_t__ OSSL_PARAM_UNSIGNED_INTEGER ; 

int OSSL_PARAM_get_double(const OSSL_PARAM *p, double *val)
{
    int64_t i64;
    uint64_t u64;

    if (val == NULL || p == NULL)
        return 0;

    if (p->data_type == OSSL_PARAM_REAL) {
        switch (p->data_size) {
        case sizeof(double):
            *val = *(const double *)p->data;
            return 1;
        }
    } else if (p->data_type == OSSL_PARAM_UNSIGNED_INTEGER) {
        switch (p->data_size) {
        case sizeof(uint32_t):
            *val = *(const uint32_t *)p->data;
            return 1;
        case sizeof(uint64_t):
            u64 = *(const uint64_t *)p->data;
            if ((u64 >> 53) == 0) { /* 53 significant bits in the mantissa */
                *val = (double)u64;
                return 1;
            }
            break;
        }
    } else if (p->data_type == OSSL_PARAM_INTEGER) {
        switch (p->data_size) {
        case sizeof(int32_t):
            *val = *(const int32_t *)p->data;
            return 1;
        case sizeof(int64_t):
            i64 = *(const int64_t *)p->data;
            u64 = i64 < 0 ? -i64 : i64;
            if ((u64 >> 53) == 0) { /* 53 significant bits in the mantissa */
                *val = 0.0 + i64;
                return 1;
            }
            break;
        }
    }
    return 0;
}