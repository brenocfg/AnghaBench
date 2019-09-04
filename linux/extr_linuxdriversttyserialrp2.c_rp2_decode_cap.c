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
struct pci_device_id {int driver_data; } ;

/* Variables and functions */

__attribute__((used)) static inline void rp2_decode_cap(const struct pci_device_id *id,
				  int *ports, int *smpte)
{
	*ports = id->driver_data >> 8;
	*smpte = id->driver_data & 0xff;
}