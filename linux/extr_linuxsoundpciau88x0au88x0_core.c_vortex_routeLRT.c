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
typedef  unsigned char ADBRamLink ;

/* Variables and functions */
 unsigned char ADB_MASK ; 
 unsigned char ADB_SHIFT ; 
 unsigned char NR_MIXOUT ; 
 unsigned char NR_SRC ; 
 unsigned char OFFSET_MIXOUT ; 
 unsigned char OFFSET_SRCOUT ; 
 int /*<<< orphan*/  vortex_adb_addroutes (int /*<<< orphan*/ *,unsigned char,unsigned char*,int) ; 
 int /*<<< orphan*/  vortex_adb_delroutes (int /*<<< orphan*/ *,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  vortex_mixer_addWTD (int /*<<< orphan*/ *,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  vortex_mixer_delWTD (int /*<<< orphan*/ *,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  vortex_src_addWTD (int /*<<< orphan*/ *,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  vortex_src_delWTD (int /*<<< orphan*/ *,unsigned char,unsigned char) ; 

__attribute__((used)) static void
vortex_routeLRT(vortex_t * vortex, int en, unsigned char ch,
		unsigned char source0, unsigned char source1,
		unsigned char dest)
{
	ADBRamLink route[2];

	route[0] = ((source0 & ADB_MASK) << ADB_SHIFT) | (dest & ADB_MASK);
	route[1] = ((source1 & ADB_MASK) << ADB_SHIFT) | (dest & ADB_MASK);

	if (dest < 0x10)
		route[1] = (route[1] & ~ADB_MASK) | (dest + 0x20);	/* fifo A */

	if (en) {
		vortex_adb_addroutes(vortex, ch, route, 2);
		if ((source0 < (OFFSET_SRCOUT + NR_SRC))
		    && (source0 >= OFFSET_SRCOUT)) {
			vortex_src_addWTD(vortex,
					  (source0 - OFFSET_SRCOUT), ch);
			vortex_src_addWTD(vortex,
					  (source1 - OFFSET_SRCOUT), ch);
		} else if ((source0 < (OFFSET_MIXOUT + NR_MIXOUT))
			   && (source0 >= OFFSET_MIXOUT)) {
			vortex_mixer_addWTD(vortex,
					    (source0 - OFFSET_MIXOUT), ch);
			vortex_mixer_addWTD(vortex,
					    (source1 - OFFSET_MIXOUT), ch);
		}
	} else {
		vortex_adb_delroutes(vortex, ch, route[0], route[1]);
		if ((source0 < (OFFSET_SRCOUT + NR_SRC))
		    && (source0 >= OFFSET_SRCOUT)) {
			vortex_src_delWTD(vortex,
					  (source0 - OFFSET_SRCOUT), ch);
			vortex_src_delWTD(vortex,
					  (source1 - OFFSET_SRCOUT), ch);
		} else if ((source0 < (OFFSET_MIXOUT + NR_MIXOUT))
			   && (source0 >= OFFSET_MIXOUT)) {
			vortex_mixer_delWTD(vortex,
					    (source0 - OFFSET_MIXOUT), ch);
			vortex_mixer_delWTD(vortex,
					    (source1 - OFFSET_MIXOUT), ch);
		}
	}
}