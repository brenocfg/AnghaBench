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
typedef  int /*<<< orphan*/  vortex_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIX_DEFIGAIN ; 
 int /*<<< orphan*/  vortex_mix_disableinput (int /*<<< orphan*/ *,unsigned char,unsigned char,int) ; 
 int /*<<< orphan*/  vortex_mix_enableinput (int /*<<< orphan*/ *,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  vortex_mix_setinputvolumebyte (int /*<<< orphan*/ *,unsigned char,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vortex_connection_mixin_mix(vortex_t * vortex, int en, unsigned char mixin,
			    unsigned char mix, int a)
{
	if (en) {
		vortex_mix_enableinput(vortex, mix, mixin);
		vortex_mix_setinputvolumebyte(vortex, mix, mixin, MIX_DEFIGAIN);	// added to original code.
	} else
		vortex_mix_disableinput(vortex, mix, mixin, a);
}