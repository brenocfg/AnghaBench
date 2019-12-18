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
struct TYPE_4__ {int /*<<< orphan*/  canon_enclen; int /*<<< orphan*/  canon_enc; } ;
typedef  TYPE_1__ X509_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_Digest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  i2d_X509_NAME (TYPE_1__*,int /*<<< orphan*/ *) ; 

unsigned long X509_NAME_hash(X509_NAME *x)
{
    unsigned long ret = 0;
    unsigned char md[SHA_DIGEST_LENGTH];

    /* Make sure X509_NAME structure contains valid cached encoding */
    i2d_X509_NAME(x, NULL);
    if (!EVP_Digest(x->canon_enc, x->canon_enclen, md, NULL, EVP_sha1(),
                    NULL))
        return 0;

    ret = (((unsigned long)md[0]) | ((unsigned long)md[1] << 8L) |
           ((unsigned long)md[2] << 16L) | ((unsigned long)md[3] << 24L)
        ) & 0xffffffffL;
    return ret;
}