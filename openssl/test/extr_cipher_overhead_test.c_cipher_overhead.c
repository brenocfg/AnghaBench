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
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  min_dtls; } ;
typedef  TYPE_1__ SSL_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 TYPE_1__* ssl3_get_cipher (int) ; 
 int ssl3_num_ciphers () ; 
 int /*<<< orphan*/  ssl_cipher_get_overhead (TYPE_1__ const*,size_t*,size_t*,size_t*,size_t*) ; 

__attribute__((used)) static int cipher_overhead(void)
{
    int ret = 1, i, n = ssl3_num_ciphers();
    const SSL_CIPHER *ciph;
    size_t mac, in, blk, ex;

    for (i = 0; i < n; i++) {
        ciph = ssl3_get_cipher(i);
        if (!ciph->min_dtls)
            continue;
        if (!TEST_true(ssl_cipher_get_overhead(ciph, &mac, &in, &blk, &ex))) {
            TEST_info("Failed getting %s", ciph->name);
            ret = 0;
        } else {
            TEST_info("Cipher %s: %zu %zu %zu %zu",
                      ciph->name, mac, in, blk, ex);
        }
    }
    return ret;
}