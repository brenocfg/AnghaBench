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
typedef  int /*<<< orphan*/  ut8 ;

/* Variables and functions */
 char* r_str_ndup (char const*,int) ; 

__attribute__((used)) static char *readString (ut8 *p, int off, int len) {
	if (off < 0 || off >= len) {
		return NULL;
	}
	return r_str_ndup ((const char *)p + off, len - off);
}