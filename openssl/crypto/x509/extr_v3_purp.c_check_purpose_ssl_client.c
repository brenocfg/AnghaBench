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
typedef  int /*<<< orphan*/  X509_PURPOSE ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int KU_DIGITAL_SIGNATURE ; 
 int KU_KEY_AGREEMENT ; 
 int /*<<< orphan*/  NS_SSL_CLIENT ; 
 int /*<<< orphan*/  XKU_SSL_CLIENT ; 
 int check_ssl_ca (int /*<<< orphan*/  const*) ; 
 scalar_t__ ku_reject (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ ns_reject (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ xku_reject (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_purpose_ssl_client(const X509_PURPOSE *xp, const X509 *x,
                                    int ca)
{
    if (xku_reject(x, XKU_SSL_CLIENT))
        return 0;
    if (ca)
        return check_ssl_ca(x);
    /* We need to do digital signatures or key agreement */
    if (ku_reject(x, KU_DIGITAL_SIGNATURE | KU_KEY_AGREEMENT))
        return 0;
    /* nsCertType if present should allow SSL client use */
    if (ns_reject(x, NS_SSL_CLIENT))
        return 0;
    return 1;
}