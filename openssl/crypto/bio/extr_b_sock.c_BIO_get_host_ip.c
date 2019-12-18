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
typedef  int /*<<< orphan*/  BIO_ADDRINFO ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  BIO_ADDRINFO_address (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_ADDRINFO_family (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_ADDRINFO_free (int /*<<< orphan*/ *) ; 
 int BIO_ADDR_rawaddress (int /*<<< orphan*/ ,unsigned char*,size_t*) ; 
 int /*<<< orphan*/  BIO_F_BIO_GET_HOST_IP ; 
 int /*<<< orphan*/  BIO_LOOKUP_CLIENT ; 
 int /*<<< orphan*/  BIO_R_GETHOSTBYNAME_ADDR_IS_NOT_AF_INET ; 
 scalar_t__ BIO_lookup (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int BIO_sock_init () ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char const*) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ ossl_assert (int) ; 

int BIO_get_host_ip(const char *str, unsigned char *ip)
{
    BIO_ADDRINFO *res = NULL;
    int ret = 0;

    if (BIO_sock_init() != 1)
        return 0;               /* don't generate another error code here */

    if (BIO_lookup(str, NULL, BIO_LOOKUP_CLIENT, AF_INET, SOCK_STREAM, &res)) {
        size_t l;

        if (BIO_ADDRINFO_family(res) != AF_INET) {
            BIOerr(BIO_F_BIO_GET_HOST_IP,
                   BIO_R_GETHOSTBYNAME_ADDR_IS_NOT_AF_INET);
        } else if (BIO_ADDR_rawaddress(BIO_ADDRINFO_address(res), NULL, &l)) {
            /*
             * Because only AF_INET addresses will reach this far, we can assert
             * that l should be 4
             */
            if (ossl_assert(l == 4))
                ret = BIO_ADDR_rawaddress(BIO_ADDRINFO_address(res), ip, &l);
        }
        BIO_ADDRINFO_free(res);
    } else {
        ERR_add_error_data(2, "host=", str);
    }

    return ret;
}