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
typedef  int /*<<< orphan*/  u32 ;
struct ohci_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * portstatus ; 
 int /*<<< orphan*/  read_roothub (struct ohci_hcd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u32 roothub_portstatus (struct ohci_hcd *hc, int i)
	{ return read_roothub (hc, portstatus [i], 0xffe0fce0); }