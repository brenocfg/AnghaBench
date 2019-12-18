#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  void DSA ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_free (void*) ; 
 void* DSA_new () ; 
 int /*<<< orphan*/  params_to_key (void*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void *dsa_importkey(void *provctx, const OSSL_PARAM params[])
{
    DSA *dsa;

    if ((dsa = DSA_new()) == NULL
        || !params_to_key(dsa, params)) {
        DSA_free(dsa);
        dsa = NULL;
    }
    return dsa;
}