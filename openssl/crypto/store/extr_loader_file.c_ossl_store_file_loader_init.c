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

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_loader ; 
 int ossl_store_register_loader_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_file_loader_deinit ; 

int ossl_store_file_loader_init(void)
{
    int ret = ossl_store_register_loader_int(&file_loader);

    OPENSSL_atexit(store_file_loader_deinit);
    return ret;
}