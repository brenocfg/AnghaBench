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
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_STRING_type_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_ASN1_OCTET_STRING ; 

ASN1_STRING *ASN1_STRING_new(void)
{
    return ASN1_STRING_type_new(V_ASN1_OCTET_STRING);
}