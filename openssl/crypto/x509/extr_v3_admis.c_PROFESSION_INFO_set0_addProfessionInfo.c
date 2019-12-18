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
struct TYPE_3__ {int /*<<< orphan*/ * addProfessionInfo; } ;
typedef  TYPE_1__ PROFESSION_INFO ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (int /*<<< orphan*/ *) ; 

void PROFESSION_INFO_set0_addProfessionInfo(PROFESSION_INFO *pi,
                                            ASN1_OCTET_STRING *aos)
{
    ASN1_OCTET_STRING_free(pi->addProfessionInfo);
    pi->addProfessionInfo = aos;
}