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
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,size_t) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_octet_string (TYPE_1__ const*,void**,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int scrypt_set_membuf(unsigned char **buffer, size_t *buflen,
                             const OSSL_PARAM *p)
{
    OPENSSL_clear_free(*buffer, *buflen);
    if (p->data_size == 0) {
        if ((*buffer = OPENSSL_malloc(1)) == NULL) {
            ERR_raise(ERR_LIB_PROV, ERR_R_MALLOC_FAILURE);
            return 0;
        }
    } else if (p->data != NULL) {
        *buffer = NULL;
        if (!OSSL_PARAM_get_octet_string(p, (void **)buffer, 0, buflen))
            return 0;
    }
    return 1;
}