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
 int /*<<< orphan*/  ADB_MIXOUT (unsigned char) ; 
 int /*<<< orphan*/  ADB_SRCIN (unsigned char) ; 
 int /*<<< orphan*/  MIX_DEFOGAIN ; 
 int /*<<< orphan*/  vortex_mix_setvolumebyte (int /*<<< orphan*/ *,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_route (int /*<<< orphan*/ *,int,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vortex_connection_mix_src(vortex_t * vortex, int en, unsigned char ch,
			  unsigned char mix, unsigned char src)
{
	vortex_route(vortex, en, ch, ADB_MIXOUT(mix), ADB_SRCIN(src));
	vortex_mix_setvolumebyte(vortex, mix, MIX_DEFOGAIN);	// added to original code.
}