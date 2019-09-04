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
typedef  int /*<<< orphan*/  OSSL_STORE_LOADER ;

/* Variables and functions */
 int /*<<< orphan*/  ossl_store_init_once () ; 
 int ossl_store_register_loader_int (int /*<<< orphan*/ *) ; 

int OSSL_STORE_register_loader(OSSL_STORE_LOADER *loader)
{
    if (!ossl_store_init_once())
        return 0;
    return ossl_store_register_loader_int(loader);
}