#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * namingAuthorityUrl; } ;
typedef  TYPE_1__ NAMING_AUTHORITY ;
typedef  int /*<<< orphan*/  ASN1_IA5STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_IA5STRING_free (int /*<<< orphan*/ *) ; 

void NAMING_AUTHORITY_set0_authorityURL(NAMING_AUTHORITY *n, ASN1_IA5STRING* u)
{
    ASN1_IA5STRING_free(n->namingAuthorityUrl);
    n->namingAuthorityUrl = u;
}