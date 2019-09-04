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
struct TYPE_3__ {int depth; int size; unsigned int* indexes; } ;
typedef  TYPE_1__ BN_STACK ;

/* Variables and functions */
 int BN_CTX_START_FRAMES ; 
 int /*<<< orphan*/  BN_F_BN_STACK_PUSH ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned int*) ; 
 unsigned int* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned int*,int) ; 

__attribute__((used)) static int BN_STACK_push(BN_STACK *st, unsigned int idx)
{
    if (st->depth == st->size) {
        /* Need to expand */
        unsigned int newsize =
            st->size ? (st->size * 3 / 2) : BN_CTX_START_FRAMES;
        unsigned int *newitems;

        if ((newitems = OPENSSL_malloc(sizeof(*newitems) * newsize)) == NULL) {
            BNerr(BN_F_BN_STACK_PUSH, ERR_R_MALLOC_FAILURE);
            return 0;
        }
        if (st->depth)
            memcpy(newitems, st->indexes, sizeof(*newitems) * st->depth);
        OPENSSL_free(st->indexes);
        st->indexes = newitems;
        st->size = newsize;
    }
    st->indexes[(st->depth)++] = idx;
    return 1;
}