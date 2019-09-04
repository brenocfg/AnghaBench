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
struct TYPE_3__ {int /*<<< orphan*/  iplen; int /*<<< orphan*/  ip; } ;
typedef  TYPE_1__ X509_VERIFY_PARAM ;

/* Variables and functions */
 int int_x509_param_set1 (char**,int /*<<< orphan*/ *,char*,size_t) ; 

int X509_VERIFY_PARAM_set1_ip(X509_VERIFY_PARAM *param,
                              const unsigned char *ip, size_t iplen)
{
    if (iplen != 0 && iplen != 4 && iplen != 16)
        return 0;
    return int_x509_param_set1((char **)&param->ip, &param->iplen,
                               (char *)ip, iplen);
}