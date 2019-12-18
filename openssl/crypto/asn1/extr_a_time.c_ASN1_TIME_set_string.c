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
typedef  int /*<<< orphan*/  ASN1_TIME ;

/* Variables and functions */
 int ASN1_GENERALIZEDTIME_set_string (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ ASN1_UTCTIME_set_string (int /*<<< orphan*/ *,char const*) ; 

int ASN1_TIME_set_string(ASN1_TIME *s, const char *str)
{
    /* Try UTC, if that fails, try GENERALIZED */
    if (ASN1_UTCTIME_set_string(s, str))
        return 1;
    return ASN1_GENERALIZEDTIME_set_string(s, str);
}