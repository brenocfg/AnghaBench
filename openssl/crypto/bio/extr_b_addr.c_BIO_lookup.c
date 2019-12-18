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
typedef  enum BIO_lookup_type { ____Placeholder_BIO_lookup_type } BIO_lookup_type ;
typedef  int /*<<< orphan*/  BIO_ADDRINFO ;

/* Variables and functions */
 int BIO_lookup_ex (char const*,char const*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

int BIO_lookup(const char *host, const char *service,
               enum BIO_lookup_type lookup_type,
               int family, int socktype, BIO_ADDRINFO **res)
{
    return BIO_lookup_ex(host, service, lookup_type, family, socktype, 0, res);
}