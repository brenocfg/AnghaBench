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
struct TYPE_5__ {int flags; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ DH_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  DH_F_DH_METH_NEW ; 
 int /*<<< orphan*/  DHerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/ * OPENSSL_strdup (char const*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 

DH_METHOD *DH_meth_new(const char *name, int flags)
{
    DH_METHOD *dhm = OPENSSL_zalloc(sizeof(*dhm));

    if (dhm != NULL) {
        dhm->flags = flags;

        dhm->name = OPENSSL_strdup(name);
        if (dhm->name != NULL)
            return dhm;

        OPENSSL_free(dhm);
    }

    DHerr(DH_F_DH_METH_NEW, ERR_R_MALLOC_FAILURE);
    return NULL;
}