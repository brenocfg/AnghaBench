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
typedef  int /*<<< orphan*/  OSSL_PROVIDER ;
typedef  int /*<<< orphan*/  OSSL_ALGORITHM ;

/* Variables and functions */
#define  OSSL_OP_DIGEST 128 
 int /*<<< orphan*/  const* legacy_digests ; 

__attribute__((used)) static const OSSL_ALGORITHM *legacy_query(OSSL_PROVIDER *prov,
                                          int operation_id,
                                          int *no_cache)
{
    *no_cache = 0;
    switch (operation_id) {
    case OSSL_OP_DIGEST:
        return legacy_digests;
    }
    return NULL;
}