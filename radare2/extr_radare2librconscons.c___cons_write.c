#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fdout; } ;

/* Variables and functions */
 TYPE_1__ I ; 
 int /*<<< orphan*/  write (int,char const*,int) ; 

__attribute__((used)) static inline void __cons_write(const char *buf, int len) {
#if __WINDOWS__
	if (I.ansicon) {
		(void) write (I.fdout, buf, len);
	} else {
		if (I.fdout == 1) {
			r_cons_w32_print ((const ut8*)buf, len, 0);
		} else {
			(void) write (I.fdout, buf, len);
		}
	}
#else
	if (I.fdout < 1) {
		I.fdout = 1;
	}
	(void) write (I.fdout, buf, len);
#endif
}