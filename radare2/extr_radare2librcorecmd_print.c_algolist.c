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
typedef  unsigned long long ut64 ;

/* Variables and functions */
 int R_HASH_NBITS ; 
 int /*<<< orphan*/  r_cons_newline () ; 
 int /*<<< orphan*/  r_cons_printf (char*,char const*) ; 
 int /*<<< orphan*/  r_cons_println (char const*) ; 
 char* r_hash_name (unsigned long long) ; 

__attribute__((used)) static void algolist(int mode) {
	int i;
	for (i = 0; i < R_HASH_NBITS; i++) {
		ut64 bits = 1ULL << i;
		const char *name = r_hash_name (bits);
		if (name && *name) {
			if (mode) {
				r_cons_println (name);
			} else {
				r_cons_printf ("%s ", name);
			}
		}
	}
	if (!mode) {
		r_cons_newline ();
	}
}