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
typedef  int /*<<< orphan*/  X509_VERIFY_PARAM ;

/* Variables and functions */
 int X509_VERIFY_PARAM_set1_ip (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 scalar_t__ a2i_ipadd (unsigned char*,char const*) ; 

int X509_VERIFY_PARAM_set1_ip_asc(X509_VERIFY_PARAM *param, const char *ipasc)
{
    unsigned char ipout[16];
    size_t iplen;

    iplen = (size_t)a2i_ipadd(ipout, ipasc);
    if (iplen == 0)
        return 0;
    return X509_VERIFY_PARAM_set1_ip(param, ipout, iplen);
}