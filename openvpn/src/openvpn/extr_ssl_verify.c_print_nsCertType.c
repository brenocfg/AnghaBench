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

/* Variables and functions */
#define  NS_CERT_CHECK_CLIENT 129 
#define  NS_CERT_CHECK_SERVER 128 

__attribute__((used)) static const char *
print_nsCertType(int type)
{
    switch (type)
    {
        case NS_CERT_CHECK_SERVER:
            return "SERVER";

        case NS_CERT_CHECK_CLIENT:
            return "CLIENT";

        default:
            return "?";
    }
}