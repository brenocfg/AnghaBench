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
struct hermes {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HERMES_AUXDATA ; 
 int /*<<< orphan*/  hermes_aux_setaddr (struct hermes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hermes_write_bytes (struct hermes*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hermes_program_bytes(struct hermes *hw, const char *data,
				u32 addr, u32 len)
{
	/* wl lkm splits the programming into chunks of 2000 bytes.
	 * This restriction appears to come from USB. The PCMCIA
	 * adapters can program the whole lot in one go */
	hermes_aux_setaddr(hw, addr);
	hermes_write_bytes(hw, HERMES_AUXDATA, data, len);
	return 0;
}