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
typedef  int ut8 ;
typedef  int ut64 ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  memcmp (int const*,char*,int) ; 

__attribute__((used)) static bool check_bytes(const ut8 *buf, ut64 length) {
	if (buf && length >= 32 && !memcmp (buf, "MENUET0", 7)) {
		switch (buf[7]) {
		case '0':
		case '1':
		case '2':
			return true;
		}
		eprintf ("Unsupported MENUET version header\n");
	}
	return false;
}