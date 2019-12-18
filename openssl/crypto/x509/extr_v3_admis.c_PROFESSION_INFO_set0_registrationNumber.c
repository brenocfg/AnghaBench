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
struct TYPE_3__ {int /*<<< orphan*/ * registrationNumber; } ;
typedef  TYPE_1__ PROFESSION_INFO ;
typedef  int /*<<< orphan*/  ASN1_PRINTABLESTRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_PRINTABLESTRING_free (int /*<<< orphan*/ *) ; 

void PROFESSION_INFO_set0_registrationNumber(PROFESSION_INFO *pi,
                                             ASN1_PRINTABLESTRING *rn)
{
    ASN1_PRINTABLESTRING_free(pi->registrationNumber);
    pi->registrationNumber = rn;
}