#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned char* data; scalar_t__ flags; int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ASN1_UTCTIME ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_copy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ASN1_UTCTIME_check (TYPE_1__*) ; 
 int /*<<< orphan*/  V_ASN1_UTCTIME ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int ASN1_UTCTIME_set_string(ASN1_UTCTIME *s, const char *str)
{
    ASN1_UTCTIME t;

    t.type = V_ASN1_UTCTIME;
    t.length = strlen(str);
    t.data = (unsigned char *)str;
    t.flags = 0;

    if (!ASN1_UTCTIME_check(&t))
        return 0;

    if (s != NULL && !ASN1_STRING_copy(s, &t))
        return 0;

    return 1;
}