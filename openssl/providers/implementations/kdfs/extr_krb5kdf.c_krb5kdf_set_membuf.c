#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,size_t) ; 
 int OSSL_PARAM_get_octet_string (int /*<<< orphan*/  const*,void**,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int krb5kdf_set_membuf(unsigned char **dst, size_t *dst_len,
                              const OSSL_PARAM *p)
{
    OPENSSL_clear_free(*dst, *dst_len);
    *dst = NULL;
    return OSSL_PARAM_get_octet_string(p, (void **)dst, 0, dst_len);
}