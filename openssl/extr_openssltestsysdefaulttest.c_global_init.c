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
 int OPENSSL_INIT_ENGINE_ALL_BUILTIN ; 
 int OPENSSL_INIT_LOAD_CONFIG ; 
 int /*<<< orphan*/  OPENSSL_init_ssl (int,int /*<<< orphan*/ *) ; 

int global_init(void)
{
    if (!OPENSSL_init_ssl(OPENSSL_INIT_ENGINE_ALL_BUILTIN
                          | OPENSSL_INIT_LOAD_CONFIG, NULL))
        return 0;
    return 1;
}