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
struct efx_farch_filter_spec {scalar_t__ type; int flags; scalar_t__ dmaq_id; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EFX_FILTER_FLAG_TX ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool efx_farch_filter_equal(const struct efx_farch_filter_spec *left,
				   const struct efx_farch_filter_spec *right)
{
	if (left->type != right->type ||
	    memcmp(left->data, right->data, sizeof(left->data)))
		return false;

	if (left->flags & EFX_FILTER_FLAG_TX &&
	    left->dmaq_id != right->dmaq_id)
		return false;

	return true;
}