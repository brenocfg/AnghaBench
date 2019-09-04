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
typedef  int ut64 ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,char*,int) ; 

__attribute__((used)) static bool check_bytes(const ut8 *buf, ut64 length) {
	if (buf && length >= 4) {
		if (!memcmp (buf, "\xce\xfa\xed\xfe", 4) ||
			!memcmp (buf, "\xfe\xed\xfa\xce", 4)) {
			return true;
		}
	}
	return false;
}