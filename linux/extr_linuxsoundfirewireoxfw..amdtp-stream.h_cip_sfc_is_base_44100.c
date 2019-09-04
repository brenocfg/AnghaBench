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
typedef  enum cip_sfc { ____Placeholder_cip_sfc } cip_sfc ;

/* Variables and functions */

__attribute__((used)) static inline bool cip_sfc_is_base_44100(enum cip_sfc sfc)
{
	return sfc & 1;
}