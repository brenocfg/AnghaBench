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
typedef  scalar_t__ ut64 ;

/* Variables and functions */
 scalar_t__ sdb_now () ; 

__attribute__((used)) static inline ut64 parse_expire (ut64 e) {
	const ut64 month = 30 * 24 * 60 * 60;
	if (e > 0 && e < month) {
		e += sdb_now ();
	}
	return e;
}