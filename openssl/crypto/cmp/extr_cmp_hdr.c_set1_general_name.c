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
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_6__ {int /*<<< orphan*/ * directoryName; } ;
struct TYPE_7__ {TYPE_1__ d; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ GENERAL_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  GENERAL_NAME_free (TYPE_2__*) ; 
 TYPE_2__* GENERAL_NAME_new () ; 
 int /*<<< orphan*/  GEN_DIRNAME ; 
 int /*<<< orphan*/ * X509_NAME_new () ; 
 int /*<<< orphan*/  X509_NAME_set (int /*<<< orphan*/ **,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ossl_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set1_general_name(GENERAL_NAME **tgt, const X509_NAME *src)
{
    GENERAL_NAME *gen;

    if (!ossl_assert(tgt != NULL))
        return 0;
    if ((gen = GENERAL_NAME_new()) == NULL)
        goto err;
    gen->type = GEN_DIRNAME;

    if (src == NULL) { /* NULL-DN */
        if ((gen->d.directoryName = X509_NAME_new()) == NULL)
            goto err;
    } else if (!X509_NAME_set(&gen->d.directoryName, src)) {
        goto err;
    }

    GENERAL_NAME_free(*tgt);
    *tgt = gen;

    return 1;

 err:
    GENERAL_NAME_free(gen);
    return 0;
}