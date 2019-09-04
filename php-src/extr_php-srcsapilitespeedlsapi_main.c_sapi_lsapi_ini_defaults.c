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
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */

__attribute__((used)) static void sapi_lsapi_ini_defaults(HashTable *configuration_hash)
{
#if PHP_MAJOR_VERSION > 4
/*
    zval *tmp, *entry;

    MAKE_STD_ZVAL(tmp);

    INI_DEFAULT("register_long_arrays", "0");

    FREE_ZVAL(tmp);
*/
#endif

}