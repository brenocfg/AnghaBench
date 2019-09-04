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
struct TYPE_3__ {unsigned int data_type; size_t data_size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ OSSL_PARAM ;

/* Variables and functions */
 char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int get_string_internal(const OSSL_PARAM *p, void **val, size_t max_len,
                               size_t *used_len, unsigned int type)
{
    size_t sz;

    if (val == NULL || p == NULL || p->data_type != type)
        return 0;

    sz = p->data_size;

    if (used_len != NULL)
        *used_len = sz;

    if (*val == NULL) {
        char *const q = OPENSSL_malloc(sz);

        if (q == NULL)
            return 0;
        *val = q;
        memcpy(q, p->data, sz);
        return 1;
    }
    if (max_len < sz)
        return 0;
    memcpy(*val, p->data, sz);
    return 1;
}