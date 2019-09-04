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
typedef  int ut16 ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static bool check_preludes(ut8 *buf, ut16 bufsz) {
	if (bufsz < 10) {
		return false;
	}
	if (!memcmp (buf, (const ut8 *) "\x55\x89\xe5", 3)) {
		return true;
	} else if (!memcmp (buf, (const ut8 *) "\x55\x8b\xec", 3)) {
		return true;
	} else if (!memcmp (buf, (const ut8 *) "\x8b\xff", 2)) {
		return true;
	} else if (!memcmp (buf, (const ut8 *) "\x55\x48\x89\xe5", 4)) {
		return true;
	} else if (!memcmp (buf, (const ut8 *) "\x55\x48\x8b\xec", 4)) {
		return true;
	}
	return false;
}