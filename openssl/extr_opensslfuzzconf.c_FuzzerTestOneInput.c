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
typedef  int /*<<< orphan*/  CONF ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 scalar_t__ BIO_write (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  NCONF_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NCONF_load_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/ * NCONF_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 

int FuzzerTestOneInput(const uint8_t *buf, size_t len)
{
    CONF *conf;
    BIO *in;
    long eline;

    if (len == 0)
        return 0;

    conf = NCONF_new(NULL);
    in = BIO_new(BIO_s_mem());
    OPENSSL_assert((size_t)BIO_write(in, buf, len) == len);
    NCONF_load_bio(conf, in, &eline);
    NCONF_free(conf);
    BIO_free(in);
    ERR_clear_error();

    return 0;
}