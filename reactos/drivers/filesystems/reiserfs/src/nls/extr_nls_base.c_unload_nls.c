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
struct nls_table {scalar_t__ owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  __MOD_DEC_USE_COUNT (scalar_t__) ; 

void unload_nls(struct nls_table *nls)
{
	if (nls->owner)
		__MOD_DEC_USE_COUNT(nls->owner);
}