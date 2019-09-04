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
struct td {int /*<<< orphan*/ * hwPSW; } ;
struct ohci_hcd {int dummy; } ;
typedef  int /*<<< orphan*/  __hc16 ;

/* Variables and functions */
 scalar_t__ big_endian_desc (struct ohci_hcd const*) ; 

__attribute__((used)) static inline __hc16 *ohci_hwPSWp(const struct ohci_hcd *ohci,
                                 const struct td *td, int index)
{
	return (__hc16 *)(big_endian_desc(ohci) ?
			&td->hwPSW[index ^ 1] : &td->hwPSW[index]);
}