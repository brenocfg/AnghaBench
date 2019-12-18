#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; int /*<<< orphan*/  ref_lock; int /*<<< orphan*/  ref_offset; } ;
struct TYPE_5__ {scalar_t__ itype; char* sname; TYPE_2__* funcs; } ;
typedef  int /*<<< orphan*/  CRYPTO_RWLOCK ;
typedef  int CRYPTO_REF_COUNT ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  TYPE_1__ ASN1_ITEM ;
typedef  TYPE_2__ ASN1_AUX ;

/* Variables and functions */
 int ASN1_AFLG_REFCOUNT ; 
 int /*<<< orphan*/  ASN1_F_ASN1_DO_LOCK ; 
 scalar_t__ ASN1_ITYPE_NDEF_SEQUENCE ; 
 scalar_t__ ASN1_ITYPE_SEQUENCE ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_DOWN_REF (int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  CRYPTO_UP_REF (int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  REF_ASSERT_ISNT (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,TYPE_1__ const*,int,char*) ; 
 void* offset2ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int asn1_do_lock(ASN1_VALUE **pval, int op, const ASN1_ITEM *it)
{
    const ASN1_AUX *aux;
    CRYPTO_REF_COUNT *lck;
    CRYPTO_RWLOCK **lock;
    int ret = -1;

    if ((it->itype != ASN1_ITYPE_SEQUENCE)
        && (it->itype != ASN1_ITYPE_NDEF_SEQUENCE))
        return 0;
    aux = it->funcs;
    if (aux == NULL || (aux->flags & ASN1_AFLG_REFCOUNT) == 0)
        return 0;
    lck = offset2ptr(*pval, aux->ref_offset);
    lock = offset2ptr(*pval, aux->ref_lock);

    switch (op) {
    case 0:
        *lck = ret = 1;
        *lock = CRYPTO_THREAD_lock_new();
        if (*lock == NULL) {
            ASN1err(ASN1_F_ASN1_DO_LOCK, ERR_R_MALLOC_FAILURE);
            return -1;
        }
        break;
    case 1:
        if (!CRYPTO_UP_REF(lck, &ret, *lock))
            return -1;
        break;
    case -1:
        if (!CRYPTO_DOWN_REF(lck, &ret, *lock))
            return -1;  /* failed */
#ifdef REF_PRINT
        fprintf(stderr, "%p:%4d:%s\n", it, ret, it->sname);
#endif
        REF_ASSERT_ISNT(ret < 0);
        if (ret == 0) {
            CRYPTO_THREAD_lock_free(*lock);
            *lock = NULL;
        }
        break;
    }

    return ret;
}