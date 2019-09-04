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
struct dlm_protocol_version {scalar_t__ pv_major; scalar_t__ pv_minor; } ;

/* Variables and functions */

__attribute__((used)) static int dlm_protocol_compare(struct dlm_protocol_version *existing,
				struct dlm_protocol_version *request)
{
	if (existing->pv_major != request->pv_major)
		return 1;

	if (existing->pv_minor > request->pv_minor)
		return 1;

	if (existing->pv_minor < request->pv_minor)
		request->pv_minor = existing->pv_minor;

	return 0;
}