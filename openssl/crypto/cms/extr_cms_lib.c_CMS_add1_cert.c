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
typedef  int /*<<< orphan*/  CMS_ContentInfo ;

/* Variables and functions */
 int CMS_add0_cert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_up_ref (int /*<<< orphan*/ *) ; 

int CMS_add1_cert(CMS_ContentInfo *cms, X509 *cert)
{
    int r;
    r = CMS_add0_cert(cms, cert);
    if (r > 0)
        X509_up_ref(cert);
    return r;
}