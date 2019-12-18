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
typedef  int /*<<< orphan*/  OSSL_NAMEMAP ;

/* Variables and functions */
 int /*<<< orphan*/  ossl_namemap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_namemap_new () ; 
 scalar_t__ test_namemap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_namemap_independent(void)
{
    OSSL_NAMEMAP *nm = ossl_namemap_new();
    int ok = nm != NULL && test_namemap(nm);

    ossl_namemap_free(nm);
    return ok;
}