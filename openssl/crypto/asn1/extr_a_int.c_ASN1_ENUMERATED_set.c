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
typedef  int /*<<< orphan*/  ASN1_ENUMERATED ;

/* Variables and functions */
 int ASN1_ENUMERATED_set_int64 (int /*<<< orphan*/ *,long) ; 

int ASN1_ENUMERATED_set(ASN1_ENUMERATED *a, long v)
{
    return ASN1_ENUMERATED_set_int64(a, v);
}