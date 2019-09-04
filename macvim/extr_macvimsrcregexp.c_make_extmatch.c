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
struct TYPE_3__ {int refcnt; } ;
typedef  TYPE_1__ reg_extmatch_T ;

/* Variables and functions */
 scalar_t__ alloc_clear (unsigned int) ; 

__attribute__((used)) static reg_extmatch_T *
make_extmatch()
{
    reg_extmatch_T	*em;

    em = (reg_extmatch_T *)alloc_clear((unsigned)sizeof(reg_extmatch_T));
    if (em != NULL)
	em->refcnt = 1;
    return em;
}