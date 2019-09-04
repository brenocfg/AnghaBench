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
struct b43legacy_wl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43legacyerr (struct b43legacy_wl*,char*) ; 

__attribute__((used)) static void b43legacy_print_fw_helptext(struct b43legacy_wl *wl)
{
	b43legacyerr(wl, "You must go to http://wireless.kernel.org/en/users/"
		     "Drivers/b43#devicefirmware "
		     "and download the correct firmware (version 3).\n");
}