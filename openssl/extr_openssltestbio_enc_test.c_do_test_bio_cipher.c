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
 int /*<<< orphan*/ * IV ; 
 int /*<<< orphan*/  KEY ; 
 int do_bio_cipher (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_test_bio_cipher(const EVP_CIPHER* cipher, int idx)
{
    switch(idx)
    {
        case 0:
            return do_bio_cipher(cipher, KEY, NULL);
        case 1:
            return do_bio_cipher(cipher, KEY, IV);
    }
    return 0;
}