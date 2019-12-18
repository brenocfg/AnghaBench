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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_printf (int /*<<< orphan*/ *,char*,char const*,char*) ; 
 char* OPENSSL_buf2hexstr (unsigned char const*,long) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 

__attribute__((used)) static int print_mac(BIO *bio, const char *label, const unsigned char *mac,
                     size_t len)
{
    int ret;
    char *hexstr = NULL;

    hexstr = OPENSSL_buf2hexstr(mac, (long)len);
    if (hexstr == NULL)
        return 0;
    ret = BIO_printf(bio, "%s = %s\n", label, hexstr);
    OPENSSL_free(hexstr);
    return ret;
}