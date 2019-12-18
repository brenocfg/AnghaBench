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
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_IPADD ; 
 scalar_t__ a2i_ipadd (unsigned char*,char const*) ; 
 int do_x509_check (int /*<<< orphan*/ *,char*,size_t,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int X509_check_ip_asc(X509 *x, const char *ipasc, unsigned int flags)
{
    unsigned char ipout[16];
    size_t iplen;

    if (ipasc == NULL)
        return -2;
    iplen = (size_t)a2i_ipadd(ipout, ipasc);
    if (iplen == 0)
        return -2;
    return do_x509_check(x, (char *)ipout, iplen, flags, GEN_IPADD, NULL);
}