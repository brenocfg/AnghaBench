#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int canon_enclen; int /*<<< orphan*/  canon_enc; scalar_t__ modified; } ;
typedef  TYPE_1__ X509_NAME ;

/* Variables and functions */
 int i2d_X509_NAME (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int X509_NAME_cmp(const X509_NAME *a, const X509_NAME *b)
{
    int ret;

    /* Ensure canonical encoding is present and up to date */

    if (!a->canon_enc || a->modified) {
        ret = i2d_X509_NAME((X509_NAME *)a, NULL);
        if (ret < 0)
            return -2;
    }

    if (!b->canon_enc || b->modified) {
        ret = i2d_X509_NAME((X509_NAME *)b, NULL);
        if (ret < 0)
            return -2;
    }

    ret = a->canon_enclen - b->canon_enclen;

    if (ret != 0 || a->canon_enclen == 0)
        return ret;

    return memcmp(a->canon_enc, b->canon_enc, a->canon_enclen);

}