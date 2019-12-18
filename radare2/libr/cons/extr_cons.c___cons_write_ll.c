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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_2__ {int fdout; scalar_t__ ansicon; } ;

/* Variables and functions */
 TYPE_1__ I ; 
 int /*<<< orphan*/  r_cons_w32_print (int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  write (int,char const*,int) ; 

__attribute__((used)) static inline void __cons_write_ll(const char *buf, int len) {
#if __WINDOWS__
	if (I.ansicon) {
		(void) write (I.fdout, buf, len);
	} else {
		if (I.fdout == 1) {
			r_cons_w32_print ((const ut8*)buf, len, false);
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