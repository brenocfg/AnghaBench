#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {scalar_t__ sigalg; } ;
typedef  TYPE_1__ SIGALG_LOOKUP ;

/* Variables and functions */
 size_t OSSL_NELEM (TYPE_1__*) ; 
 TYPE_1__* sigalg_lookup_tbl ; 

__attribute__((used)) static const SIGALG_LOOKUP *tls1_lookup_sigalg(uint16_t sigalg)
{
    size_t i;
    const SIGALG_LOOKUP *s;

    for (i = 0, s = sigalg_lookup_tbl; i < OSSL_NELEM(sigalg_lookup_tbl);
         i++, s++) {
        if (s->sigalg == sigalg)
            return s;
    }
    return NULL;
}