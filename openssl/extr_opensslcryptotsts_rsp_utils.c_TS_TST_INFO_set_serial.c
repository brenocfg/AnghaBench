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
struct TYPE_3__ {int /*<<< orphan*/  const* serial; } ;
typedef  TYPE_1__ TS_TST_INFO ;
typedef  int /*<<< orphan*/  const ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  const* ASN1_INTEGER_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  TS_F_TS_TST_INFO_SET_SERIAL ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int TS_TST_INFO_set_serial(TS_TST_INFO *a, const ASN1_INTEGER *serial)
{
    ASN1_INTEGER *new_serial;

    if (a->serial == serial)
        return 1;
    new_serial = ASN1_INTEGER_dup(serial);
    if (new_serial == NULL) {
        TSerr(TS_F_TS_TST_INFO_SET_SERIAL, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    ASN1_INTEGER_free(a->serial);
    a->serial = new_serial;
    return 1;
}