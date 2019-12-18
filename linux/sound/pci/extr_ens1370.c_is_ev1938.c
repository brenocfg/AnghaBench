#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ensoniq {TYPE_1__* pci; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */

__attribute__((used)) static inline bool is_ev1938(struct ensoniq *ensoniq)
{
	return ensoniq->pci->device == 0x8938;
}