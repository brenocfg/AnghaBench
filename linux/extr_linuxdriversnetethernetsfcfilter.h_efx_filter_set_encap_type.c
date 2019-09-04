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
struct efx_filter_spec {int encap_type; int /*<<< orphan*/  match_flags; } ;
typedef  enum efx_encap_type { ____Placeholder_efx_encap_type } efx_encap_type ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_FILTER_MATCH_ENCAP_TYPE ; 

__attribute__((used)) static inline void efx_filter_set_encap_type(struct efx_filter_spec *spec,
					     enum efx_encap_type encap_type)
{
	spec->match_flags |= EFX_FILTER_MATCH_ENCAP_TYPE;
	spec->encap_type = encap_type;
}