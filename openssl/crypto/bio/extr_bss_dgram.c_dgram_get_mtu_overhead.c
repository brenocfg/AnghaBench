#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct in6_addr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  peer; } ;
typedef  TYPE_1__ bio_dgram_data ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int BIO_ADDR_family (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_ADDR_rawaddress (int /*<<< orphan*/ *,struct in6_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_V4MAPPED (struct in6_addr*) ; 

__attribute__((used)) static long dgram_get_mtu_overhead(bio_dgram_data *data)
{
    long ret;

    switch (BIO_ADDR_family(&data->peer)) {
    case AF_INET:
        /*
         * Assume this is UDP - 20 bytes for IP, 8 bytes for UDP
         */
        ret = 28;
        break;
# if OPENSSL_USE_IPV6
    case AF_INET6:
        {
#  ifdef IN6_IS_ADDR_V4MAPPED
            struct in6_addr tmp_addr;
            if (BIO_ADDR_rawaddress(&data->peer, &tmp_addr, NULL)
                && IN6_IS_ADDR_V4MAPPED(&tmp_addr))
                /*
                 * Assume this is UDP - 20 bytes for IP, 8 bytes for UDP
                 */
                ret = 28;
            else
#  endif
            /*
             * Assume this is UDP - 40 bytes for IP, 8 bytes for UDP
             */
            ret = 48;
        }
        break;
# endif
    default:
        /* We don't know. Go with the historical default */
        ret = 28;
        break;
    }
    return ret;
}