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
typedef  int /*<<< orphan*/  COMP_METHOD ;

/* Variables and functions */
 char const* COMP_get_name (int /*<<< orphan*/  const*) ; 

const char *SSL_COMP_get_name(const COMP_METHOD *comp)
{
#ifndef OPENSSL_NO_COMP
    return comp ? COMP_get_name(comp) : NULL;
#else
    return NULL;
#endif
}