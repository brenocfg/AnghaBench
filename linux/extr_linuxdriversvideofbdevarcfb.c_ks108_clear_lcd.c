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
struct arcfb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ks108_set_xaddr (struct arcfb_par*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks108_set_yaddr (struct arcfb_par*,unsigned int,int) ; 
 int /*<<< orphan*/  ks108_writeb_data (struct arcfb_par*,unsigned int,unsigned char) ; 
 scalar_t__ splashval ; 

__attribute__((used)) static void ks108_clear_lcd(struct arcfb_par *par, unsigned int chipindex)
{
	int i,j;

	for (i = 0; i <= 8; i++) {
		ks108_set_yaddr(par, chipindex, i);
		ks108_set_xaddr(par, chipindex, 0);
		for (j = 0; j < 64; j++) {
			ks108_writeb_data(par, chipindex,
				(unsigned char) splashval);
		}
	}
}