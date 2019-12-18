#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; int type; TYPE_1__* meth; int /*<<< orphan*/  state; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* uninstantiate ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ RAND_DRBG ;

/* Variables and functions */
 int /*<<< orphan*/  DRBG_ERROR ; 
 int RAND_DRBG_FLAG_MASTER ; 
 int RAND_DRBG_FLAG_PRIVATE ; 
 int RAND_DRBG_FLAG_PUBLIC ; 
 int RAND_DRBG_TYPE_MASTER ; 
 int RAND_DRBG_TYPE_PRIVATE ; 
 int RAND_DRBG_TYPE_PUBLIC ; 
 int RAND_DRBG_set (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  RAND_F_RAND_DRBG_UNINSTANTIATE ; 
 int /*<<< orphan*/  RAND_R_NO_DRBG_IMPLEMENTATION_SELECTED ; 
 int /*<<< orphan*/  RANDerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* rand_drbg_flags ; 
 int* rand_drbg_type ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

int RAND_DRBG_uninstantiate(RAND_DRBG *drbg)
{
    int index = -1, type, flags;
    if (drbg->meth == NULL) {
        drbg->state = DRBG_ERROR;
        RANDerr(RAND_F_RAND_DRBG_UNINSTANTIATE,
                RAND_R_NO_DRBG_IMPLEMENTATION_SELECTED);
        return 0;
    }

    /* Clear the entire drbg->ctr struct, then reset some important
     * members of the drbg->ctr struct (e.g. keysize, df_ks) to their
     * initial values.
     */
    drbg->meth->uninstantiate(drbg);

    /* The reset uses the default values for type and flags */
    if (drbg->flags & RAND_DRBG_FLAG_MASTER)
        index = RAND_DRBG_TYPE_MASTER;
    else if (drbg->flags & RAND_DRBG_FLAG_PRIVATE)
        index = RAND_DRBG_TYPE_PRIVATE;
    else if (drbg->flags & RAND_DRBG_FLAG_PUBLIC)
        index = RAND_DRBG_TYPE_PUBLIC;

    if (index != -1) {
        flags = rand_drbg_flags[index];
        type = rand_drbg_type[index];
    } else {
        flags = drbg->flags;
        type = drbg->type;
    }
    return RAND_DRBG_set(drbg, type, flags);
}