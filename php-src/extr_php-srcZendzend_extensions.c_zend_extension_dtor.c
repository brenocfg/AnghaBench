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
typedef  int /*<<< orphan*/  zend_extension ;

/* Variables and functions */

void zend_extension_dtor(zend_extension *extension)
{
#if ZEND_EXTENSIONS_SUPPORT && !ZEND_DEBUG
	if (extension->handle && !getenv("ZEND_DONT_UNLOAD_MODULES")) {
		DL_UNLOAD(extension->handle);
	}
#endif
}