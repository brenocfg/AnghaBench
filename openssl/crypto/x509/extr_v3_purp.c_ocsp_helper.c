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
 int check_ca (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int ocsp_helper(const X509_PURPOSE *xp, const X509 *x, int ca)
{
    /*
     * Must be a valid CA.  Should we really support the "I don't know" value
     * (2)?
     */
    if (ca)
        return check_ca(x);
    /* leaf certificate is checked in OCSP_verify() */
    return 1;
}