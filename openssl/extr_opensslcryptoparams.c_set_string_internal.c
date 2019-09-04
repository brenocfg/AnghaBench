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
struct TYPE_4__ {unsigned int data_type; size_t data_size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  SET_RETURN_SIZE (TYPE_1__ const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static int set_string_internal(const OSSL_PARAM *p, const void *val, size_t len,
                               unsigned int type)
{
    SET_RETURN_SIZE(p, len);
    if (p->data_type != type || p->data_size < len)
        return 0;

    memcpy(p->data, val, len);
    return 1;
}