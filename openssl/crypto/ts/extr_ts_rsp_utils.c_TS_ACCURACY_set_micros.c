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
struct TYPE_3__ {int /*<<< orphan*/  const* micros; } ;
typedef  TYPE_1__ TS_ACCURACY ;
typedef  int /*<<< orphan*/  const ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  const* ASN1_INTEGER_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  TS_F_TS_ACCURACY_SET_MICROS ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int TS_ACCURACY_set_micros(TS_ACCURACY *a, const ASN1_INTEGER *micros)
{
    ASN1_INTEGER *new_micros = NULL;

    if (a->micros == micros)
        return 1;
    if (micros != NULL) {
        new_micros = ASN1_INTEGER_dup(micros);
        if (new_micros == NULL) {
            TSerr(TS_F_TS_ACCURACY_SET_MICROS, ERR_R_MALLOC_FAILURE);
            return 0;
        }
    }
    ASN1_INTEGER_free(a->micros);
    a->micros = new_micros;
    return 1;
}