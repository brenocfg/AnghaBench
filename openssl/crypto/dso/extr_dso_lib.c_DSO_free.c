#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int flags; int /*<<< orphan*/  lock; struct TYPE_9__* loaded_filename; struct TYPE_9__* filename; int /*<<< orphan*/  meth_data; TYPE_1__* meth; int /*<<< orphan*/  references; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* finish ) (TYPE_2__*) ;int /*<<< orphan*/  (* dso_unload ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ DSO ;

/* Variables and functions */
 scalar_t__ CRYPTO_DOWN_REF (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ ) ; 
 int DSO_FLAG_NO_UNLOAD_ON_FREE ; 
 int /*<<< orphan*/  DSO_F_DSO_FREE ; 
 int /*<<< orphan*/  DSO_R_FINISH_FAILED ; 
 int /*<<< orphan*/  DSO_R_UNLOAD_FAILED ; 
 int /*<<< orphan*/  DSOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 int /*<<< orphan*/  REF_ASSERT_ISNT (int) ; 
 int /*<<< orphan*/  REF_PRINT_COUNT (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  sk_void_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

int DSO_free(DSO *dso)
{
    int i;

    if (dso == NULL)
        return 1;

    if (CRYPTO_DOWN_REF(&dso->references, &i, dso->lock) <= 0)
        return 0;

    REF_PRINT_COUNT("DSO", dso);
    if (i > 0)
        return 1;
    REF_ASSERT_ISNT(i < 0);

    if ((dso->flags & DSO_FLAG_NO_UNLOAD_ON_FREE) == 0) {
        if ((dso->meth->dso_unload != NULL) && !dso->meth->dso_unload(dso)) {
            DSOerr(DSO_F_DSO_FREE, DSO_R_UNLOAD_FAILED);
            return 0;
        }
    }

    if ((dso->meth->finish != NULL) && !dso->meth->finish(dso)) {
        DSOerr(DSO_F_DSO_FREE, DSO_R_FINISH_FAILED);
        return 0;
    }

    sk_void_free(dso->meth_data);
    OPENSSL_free(dso->filename);
    OPENSSL_free(dso->loaded_filename);
    CRYPTO_THREAD_lock_free(dso->lock);
    OPENSSL_free(dso);
    return 1;
}