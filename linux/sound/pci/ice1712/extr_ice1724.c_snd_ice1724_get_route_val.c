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
struct snd_ice1712 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROUTE_PLAYBACK ; 
 unsigned long inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_BUG () ; 

int snd_ice1724_get_route_val(struct snd_ice1712 *ice, int shift)
{
	unsigned long val;
	unsigned char eitem;
	static const unsigned char xlate[8] = {
		0, 255, 1, 2, 255, 255, 3, 4,
	};

	val = inl(ICEMT1724(ice, ROUTE_PLAYBACK));
	val >>= shift;
	val &= 7; /* we now have 3 bits per output */
	eitem = xlate[val];
	if (eitem == 255) {
		snd_BUG();
		return 0;
	}
	return eitem;
}