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
 int NFSEXP_SECINFO_FLAGS ; 

__attribute__((used)) static bool secinfo_flags_equal(int f, int g)
{
	f &= NFSEXP_SECINFO_FLAGS;
	g &= NFSEXP_SECINFO_FLAGS;
	return f == g;
}