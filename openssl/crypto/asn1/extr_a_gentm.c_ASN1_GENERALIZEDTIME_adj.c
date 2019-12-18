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
typedef  int /*<<< orphan*/  ASN1_GENERALIZEDTIME ;

/* Variables and functions */
 struct tm* OPENSSL_gmtime (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  OPENSSL_gmtime_adj (struct tm*,int,long) ; 
 int /*<<< orphan*/  V_ASN1_GENERALIZEDTIME ; 
 int /*<<< orphan*/ * asn1_time_from_tm (int /*<<< orphan*/ *,struct tm*,int /*<<< orphan*/ ) ; 

ASN1_GENERALIZEDTIME *ASN1_GENERALIZEDTIME_adj(ASN1_GENERALIZEDTIME *s,
                                               time_t t, int offset_day,
                                               long offset_sec)
{
    struct tm *ts;
    struct tm data;

    ts = OPENSSL_gmtime(&t, &data);
    if (ts == NULL)
        return NULL;

    if (offset_day || offset_sec) {
        if (!OPENSSL_gmtime_adj(ts, offset_day, offset_sec))
            return NULL;
    }

    return asn1_time_from_tm(s, ts, V_ASN1_GENERALIZEDTIME);
}