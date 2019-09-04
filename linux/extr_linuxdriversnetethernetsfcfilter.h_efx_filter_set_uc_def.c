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
struct efx_filter_spec {int /*<<< orphan*/  match_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_FILTER_MATCH_LOC_MAC_IG ; 

__attribute__((used)) static inline int efx_filter_set_uc_def(struct efx_filter_spec *spec)
{
	spec->match_flags |= EFX_FILTER_MATCH_LOC_MAC_IG;
	return 0;
}