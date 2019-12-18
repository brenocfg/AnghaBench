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
struct TYPE_4__ {scalar_t__ data_size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int OSSL_PARAM_get_octet_string (TYPE_1__ const*,void**,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int x942kdf_set_buffer(unsigned char **out, size_t *out_len,
                              const OSSL_PARAM *p)
{
    if (p->data_size == 0 || p->data == NULL)
        return 1;

    OPENSSL_free(*out);
    *out = NULL;
    return OSSL_PARAM_get_octet_string(p, (void **)out, 0, out_len);
}