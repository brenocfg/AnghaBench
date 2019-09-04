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
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,char*,int) ; 

const char *fileType(const ut8 *buf) {
	if (!memcmp (buf, "NRO0", 4)) {
		return "nro0";
	}
	if (!memcmp (buf, "NRR0", 4)) {
		return "nrr0";
	}
	if (!memcmp (buf, "MOD0", 4)) {
		return "mod0";
	}
	if (!memcmp (buf, "NSO0", 4)) {
		return "nso0";
	}
	return NULL;
}