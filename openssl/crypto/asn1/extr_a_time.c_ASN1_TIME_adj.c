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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  ASN1_TIME ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_TIME_ADJ ; 
 int /*<<< orphan*/  ASN1_R_ERROR_GETTING_TIME ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tm* OPENSSL_gmtime (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  OPENSSL_gmtime_adj (struct tm*,int,long) ; 
 int /*<<< orphan*/  V_ASN1_UNDEF ; 
 int /*<<< orphan*/ * asn1_time_from_tm (int /*<<< orphan*/ *,struct tm*,int /*<<< orphan*/ ) ; 

ASN1_TIME *ASN1_TIME_adj(ASN1_TIME *s, time_t t,
                         int offset_day, long offset_sec)
{
    struct tm *ts;
    struct tm data;

    ts = OPENSSL_gmtime(&t, &data);
    if (ts == NULL) {
        ASN1err(ASN1_F_ASN1_TIME_ADJ, ASN1_R_ERROR_GETTING_TIME);
        return NULL;
    }
    if (offset_day || offset_sec) {
        if (!OPENSSL_gmtime_adj(ts, offset_day, offset_sec))
            return NULL;
    }
    return asn1_time_from_tm(s, ts, V_ASN1_UNDEF);
}