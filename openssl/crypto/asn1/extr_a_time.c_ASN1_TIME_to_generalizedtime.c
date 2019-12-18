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
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  ASN1_TIME ;
typedef  int /*<<< orphan*/  ASN1_GENERALIZEDTIME ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_TIME_to_tm (int /*<<< orphan*/  const*,struct tm*) ; 
 int /*<<< orphan*/  V_ASN1_GENERALIZEDTIME ; 
 int /*<<< orphan*/ * asn1_time_from_tm (int /*<<< orphan*/ *,struct tm*,int /*<<< orphan*/ ) ; 

ASN1_GENERALIZEDTIME *ASN1_TIME_to_generalizedtime(const ASN1_TIME *t,
                                                   ASN1_GENERALIZEDTIME **out)
{
    ASN1_GENERALIZEDTIME *ret = NULL;
    struct tm tm;

    if (!ASN1_TIME_to_tm(t, &tm))
        return NULL;

    if (out != NULL)
        ret = *out;

    ret = asn1_time_from_tm(ret, &tm, V_ASN1_GENERALIZEDTIME);

    if (out != NULL && ret != NULL)
        *out = ret;

    return ret;
}