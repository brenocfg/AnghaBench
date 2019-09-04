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
struct tridentfb_par {int /*<<< orphan*/  chip_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPConfig ; 
 scalar_t__ crt ; 
 scalar_t__ fp ; 
 int /*<<< orphan*/  iscyber (int /*<<< orphan*/ ) ; 
 int read3CE (struct tridentfb_par*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_flatpanel(struct tridentfb_par *par)
{
	if (fp)
		return 1;
	if (crt || !iscyber(par->chip_id))
		return 0;
	return (read3CE(par, FPConfig) & 0x10) ? 1 : 0;
}