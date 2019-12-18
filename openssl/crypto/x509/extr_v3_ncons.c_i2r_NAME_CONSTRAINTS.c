#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509V3_EXT_METHOD ;
struct TYPE_2__ {scalar_t__ excludedSubtrees; scalar_t__ permittedSubtrees; } ;
typedef  TYPE_1__ NAME_CONSTRAINTS ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  do_i2r_name_constraints (int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static int i2r_NAME_CONSTRAINTS(const X509V3_EXT_METHOD *method, void *a,
                                BIO *bp, int ind)
{
    NAME_CONSTRAINTS *ncons = a;
    do_i2r_name_constraints(method, ncons->permittedSubtrees,
                            bp, ind, "Permitted");
    if (ncons->permittedSubtrees && ncons->excludedSubtrees)
        BIO_puts(bp, "\n");
    do_i2r_name_constraints(method, ncons->excludedSubtrees,
                            bp, ind, "Excluded");
    return 1;
}