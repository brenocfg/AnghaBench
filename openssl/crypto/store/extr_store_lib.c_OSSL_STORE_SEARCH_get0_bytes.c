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
struct TYPE_3__ {size_t stringlength; unsigned char const* string; } ;
typedef  TYPE_1__ OSSL_STORE_SEARCH ;

/* Variables and functions */

const unsigned char *OSSL_STORE_SEARCH_get0_bytes(const OSSL_STORE_SEARCH
                                                  *criterion, size_t *length)
{
    *length = criterion->stringlength;
    return criterion->string;
}