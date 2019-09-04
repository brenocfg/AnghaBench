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
 int /*<<< orphan*/  ASN1_TIME_set_string_X509 (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  X509_getm_notAfter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_getm_notBefore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_gmtime_adj (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_time_adj_ex (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int set_cert_times(X509 *x, const char *startdate, const char *enddate,
                   int days)
{
    if (startdate == NULL || strcmp(startdate, "today") == 0) {
        if (X509_gmtime_adj(X509_getm_notBefore(x), 0) == NULL)
            return 0;
    } else {
        if (!ASN1_TIME_set_string_X509(X509_getm_notBefore(x), startdate))
            return 0;
    }
    if (enddate == NULL) {
        if (X509_time_adj_ex(X509_getm_notAfter(x), days, 0, NULL)
            == NULL)
            return 0;
    } else if (!ASN1_TIME_set_string_X509(X509_getm_notAfter(x), enddate)) {
        return 0;
    }
    return 1;
}