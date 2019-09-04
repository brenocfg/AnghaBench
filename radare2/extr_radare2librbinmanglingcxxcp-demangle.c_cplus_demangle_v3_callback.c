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
typedef  int /*<<< orphan*/  demangle_callbackref ;

/* Variables and functions */
 int d_demangle_callback (char const*,int,int /*<<< orphan*/ ,void*) ; 

int
cplus_demangle_v3_callback (const char *mangled, int options,
                            demangle_callbackref callback, void *opaque)
{
  return d_demangle_callback (mangled, options, callback, opaque);
}