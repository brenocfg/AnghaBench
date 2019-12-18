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
 scalar_t__ CRYPTO_memcmp (unsigned char const*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_XTS_DUPLICATED_KEYS ; 
 int /*<<< orphan*/  allow_insecure_decrypt ; 

__attribute__((used)) static int aes_xts_check_keys_differ(const unsigned char *key, size_t bytes,
                                     int enc)
{
    if ((!allow_insecure_decrypt || enc)
            && CRYPTO_memcmp(key, key + bytes, bytes) == 0) {
        ERR_raise(ERR_LIB_PROV, PROV_R_XTS_DUPLICATED_KEYS);
        return 0;
    }
    return 1;
}