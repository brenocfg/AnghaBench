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

/* Variables and functions */
 int EXFLAG_XKUSAGE ; 
 int /*<<< orphan*/  OCSP_F_OCSP_CHECK_DELEGATED ; 
 int /*<<< orphan*/  OCSP_R_MISSING_OCSPSIGNING_USAGE ; 
 int /*<<< orphan*/  OCSPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int X509_get_extended_key_usage (int /*<<< orphan*/ *) ; 
 int X509_get_extension_flags (int /*<<< orphan*/ *) ; 
 int XKU_OCSP_SIGN ; 

__attribute__((used)) static int ocsp_check_delegated(X509 *x)
{
    if ((X509_get_extension_flags(x) & EXFLAG_XKUSAGE)
        && (X509_get_extended_key_usage(x) & XKU_OCSP_SIGN))
        return 1;
    OCSPerr(OCSP_F_OCSP_CHECK_DELEGATED, OCSP_R_MISSING_OCSPSIGNING_USAGE);
    return 0;
}