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
struct TYPE_3__ {char const* key; unsigned int data_type; size_t data_size; size_t* return_size; void* data; } ;
typedef  TYPE_1__ OSSL_PARAM ;

/* Variables and functions */

__attribute__((used)) static OSSL_PARAM ossl_param_construct(const char *key, unsigned int data_type,
                                       void *data, size_t data_size,
                                       size_t *return_size)
{
    OSSL_PARAM res;

    res.key = key;
    res.data_type = data_type;
    res.data = data;
    res.data_size = data_size;
    res.return_size = return_size;
    return res;
}