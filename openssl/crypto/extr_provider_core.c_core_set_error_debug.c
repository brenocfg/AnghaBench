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

/* Variables and functions */
 int /*<<< orphan*/  ERR_set_debug (char const*,int,char const*) ; 

__attribute__((used)) static void core_set_error_debug(const OSSL_PROVIDER *prov,
                                 const char *file, int line, const char *func)
{
    ERR_set_debug(file, line, func);
}