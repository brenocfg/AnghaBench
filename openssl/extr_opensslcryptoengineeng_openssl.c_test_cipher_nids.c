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
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int EVP_CIPHER_nid (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * test_r4_40_cipher () ; 
 int /*<<< orphan*/ * test_r4_cipher () ; 

__attribute__((used)) static int test_cipher_nids(const int **nids)
{
    static int cipher_nids[4] = { 0, 0, 0, 0 };
    static int pos = 0;
    static int init = 0;

    if (!init) {
        const EVP_CIPHER *cipher;
        if ((cipher = test_r4_cipher()) != NULL)
            cipher_nids[pos++] = EVP_CIPHER_nid(cipher);
        if ((cipher = test_r4_40_cipher()) != NULL)
            cipher_nids[pos++] = EVP_CIPHER_nid(cipher);
        cipher_nids[pos] = 0;
        init = 1;
    }
    *nids = cipher_nids;
    return pos;
}