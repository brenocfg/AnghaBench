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

/* Variables and functions */
 scalar_t__ EC_R_UNKNOWN_GROUP ; 
 scalar_t__ ERR_GET_LIB (long) ; 
 scalar_t__ ERR_GET_REASON (long) ; 
 scalar_t__ ERR_LIB_EC ; 
 scalar_t__ ERR_LIB_EVP ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 long ERR_peek_error () ; 
 scalar_t__ EVP_R_UNSUPPORTED_ALGORITHM ; 

__attribute__((used)) static int key_unsupported(void)
{
    long err = ERR_peek_error();

    if (ERR_GET_LIB(err) == ERR_LIB_EVP
            && ERR_GET_REASON(err) == EVP_R_UNSUPPORTED_ALGORITHM) {
        ERR_clear_error();
        return 1;
    }
#ifndef OPENSSL_NO_EC
    /*
     * If EC support is enabled we should catch also EC_R_UNKNOWN_GROUP as an
     * hint to an unsupported algorithm/curve (e.g. if binary EC support is
     * disabled).
     */
    if (ERR_GET_LIB(err) == ERR_LIB_EC
        && ERR_GET_REASON(err) == EC_R_UNKNOWN_GROUP) {
        ERR_clear_error();
        return 1;
    }
#endif /* OPENSSL_NO_EC */
    return 0;
}