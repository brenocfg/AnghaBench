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
struct TYPE_3__ {int nid; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int NID_undef ; 
 size_t OSSL_NELEM (TYPE_1__*) ; 
 TYPE_1__* nist_curves ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int EC_curve_nist2nid(const char *name)
{
    size_t i;
    for (i = 0; i < OSSL_NELEM(nist_curves); i++) {
        if (strcmp(nist_curves[i].name, name) == 0)
            return nist_curves[i].nid;
    }
    return NID_undef;
}