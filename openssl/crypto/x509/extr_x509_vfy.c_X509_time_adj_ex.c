#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_10__ {int flags; scalar_t__ type; } ;
typedef  TYPE_1__ ASN1_TIME ;

/* Variables and functions */
 TYPE_1__* ASN1_GENERALIZEDTIME_adj (TYPE_1__*,int /*<<< orphan*/ ,int,long) ; 
 int ASN1_STRING_FLAG_MSTRING ; 
 TYPE_1__* ASN1_TIME_adj (TYPE_1__*,int /*<<< orphan*/ ,int,long) ; 
 TYPE_1__* ASN1_UTCTIME_adj (TYPE_1__*,int /*<<< orphan*/ ,int,long) ; 
 scalar_t__ V_ASN1_GENERALIZEDTIME ; 
 scalar_t__ V_ASN1_UTCTIME ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

ASN1_TIME *X509_time_adj_ex(ASN1_TIME *s,
                            int offset_day, long offset_sec, time_t *in_tm)
{
    time_t t;

    if (in_tm)
        t = *in_tm;
    else
        time(&t);

    if (s && !(s->flags & ASN1_STRING_FLAG_MSTRING)) {
        if (s->type == V_ASN1_UTCTIME)
            return ASN1_UTCTIME_adj(s, t, offset_day, offset_sec);
        if (s->type == V_ASN1_GENERALIZEDTIME)
            return ASN1_GENERALIZEDTIME_adj(s, t, offset_day, offset_sec);
    }
    return ASN1_TIME_adj(s, t, offset_day, offset_sec);
}