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
struct dll_version {scalar_t__ major; scalar_t__ minor; scalar_t__ build; scalar_t__ revision; } ;

/* Variables and functions */

__attribute__((used)) static bool dll_version_equal(struct dll_version a, struct dll_version b)
{
    return a.major == b.major &&
           a.minor == b.minor &&
           a.build == b.build &&
           a.revision == b.revision;
}