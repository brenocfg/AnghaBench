#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * scheme; } ;
typedef  TYPE_1__ OSSL_STORE_LOADER ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int store_loader_cmp(const OSSL_STORE_LOADER *a,
                            const OSSL_STORE_LOADER *b)
{
    assert(a->scheme != NULL && b->scheme != NULL);
    return strcmp(a->scheme, b->scheme);
}