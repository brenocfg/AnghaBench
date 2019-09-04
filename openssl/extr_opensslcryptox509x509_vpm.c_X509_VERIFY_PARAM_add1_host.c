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
 int /*<<< orphan*/  ADD_HOST ; 
 int int_x509_param_set_hosts (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,size_t) ; 

int X509_VERIFY_PARAM_add1_host(X509_VERIFY_PARAM *param,
                                const char *name, size_t namelen)
{
    return int_x509_param_set_hosts(param, ADD_HOST, name, namelen);
}