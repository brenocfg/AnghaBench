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
 int /*<<< orphan*/ * OPENSSL_gmtime (int /*<<< orphan*/ *,struct tm*) ; 
 int asn1_time_to_tm (struct tm*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int ASN1_TIME_to_tm(const ASN1_TIME *s, struct tm *tm)
{
    if (s == NULL) {
        time_t now_t;

        time(&now_t);
        memset(tm, 0, sizeof(*tm));
        if (OPENSSL_gmtime(&now_t, tm) != NULL)
            return 1;
        return 0;
    }

    return asn1_time_to_tm(tm, s);
}