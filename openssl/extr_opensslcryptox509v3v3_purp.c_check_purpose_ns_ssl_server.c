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
 int /*<<< orphan*/  KU_KEY_ENCIPHERMENT ; 
 int check_purpose_ssl_server (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ ku_reject (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_purpose_ns_ssl_server(const X509_PURPOSE *xp, const X509 *x,
                                       int ca)
{
    int ret;
    ret = check_purpose_ssl_server(xp, x, ca);
    if (!ret || ca)
        return ret;
    /* We need to encipher or Netscape complains */
    if (ku_reject(x, KU_KEY_ENCIPHERMENT))
        return 0;
    return ret;
}