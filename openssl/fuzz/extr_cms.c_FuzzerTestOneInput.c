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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  CMS_ContentInfo ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  BIO_s_null () ; 
 scalar_t__ BIO_write (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  CMS_ContentInfo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int /*<<< orphan*/ * d2i_CMS_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2d_CMS_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int FuzzerTestOneInput(const uint8_t *buf, size_t len)
{
    CMS_ContentInfo *cms;
    BIO *in;

    if (len == 0)
        return 0;

    in = BIO_new(BIO_s_mem());
    OPENSSL_assert((size_t)BIO_write(in, buf, len) == len);
    cms = d2i_CMS_bio(in, NULL);
    if (cms != NULL) {
        BIO *out = BIO_new(BIO_s_null());

        i2d_CMS_bio(out, cms);
        BIO_free(out);
        CMS_ContentInfo_free(cms);
    }

    BIO_free(in);
    ERR_clear_error();

    return 0;
}