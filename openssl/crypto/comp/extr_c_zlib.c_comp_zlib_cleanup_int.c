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
 int /*<<< orphan*/  DSO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zlib_dso ; 

void comp_zlib_cleanup_int(void)
{
#ifdef ZLIB_SHARED
    DSO_free(zlib_dso);
    zlib_dso = NULL;
#endif
}