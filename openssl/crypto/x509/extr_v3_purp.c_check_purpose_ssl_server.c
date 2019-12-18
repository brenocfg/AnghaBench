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
 int /*<<< orphan*/  KU_TLS ; 
 int /*<<< orphan*/  NS_SSL_SERVER ; 
 int XKU_SGC ; 
 int XKU_SSL_SERVER ; 
 int check_ssl_ca (int /*<<< orphan*/  const*) ; 
 scalar_t__ ku_reject (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ns_reject (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ xku_reject (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int check_purpose_ssl_server(const X509_PURPOSE *xp, const X509 *x,
                                    int ca)
{
    if (xku_reject(x, XKU_SSL_SERVER | XKU_SGC))
        return 0;
    if (ca)
        return check_ssl_ca(x);

    if (ns_reject(x, NS_SSL_SERVER))
        return 0;
    if (ku_reject(x, KU_TLS))
        return 0;

    return 1;

}