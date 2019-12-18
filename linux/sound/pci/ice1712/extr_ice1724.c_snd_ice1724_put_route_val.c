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
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int /*<<< orphan*/ ) ; 

int snd_ice1724_put_route_val(struct snd_ice1712 *ice, unsigned int val,
								int shift)
{
	unsigned int old_val, nval;
	int change;
	static const unsigned char xroute[8] = {
		0, /* PCM */
		2, /* PSDIN0 Left */
		3, /* PSDIN0 Right */
		6, /* SPDIN Left */
		7, /* SPDIN Right */
	};

	nval = xroute[val % 5];
	val = old_val = inl(ICEMT1724(ice, ROUTE_PLAYBACK));
	val &= ~(0x07 << shift);
	val |= nval << shift;
	change = val != old_val;
	if (change)
		outl(val, ICEMT1724(ice, ROUTE_PLAYBACK));
	return change;
}