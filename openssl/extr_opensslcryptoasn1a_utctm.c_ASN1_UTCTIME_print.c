#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  BIO ;
typedef  TYPE_1__ ASN1_UTCTIME ;

/* Variables and functions */
 int ASN1_TIME_print (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 scalar_t__ V_ASN1_UTCTIME ; 

int ASN1_UTCTIME_print(BIO *bp, const ASN1_UTCTIME *tm)
{
    if (tm->type != V_ASN1_UTCTIME)
        return 0;
    return ASN1_TIME_print(bp, tm);
}