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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int r_buf_read_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool check_buffer(RBuffer *buf) {
	ut8 tmp[8];
	int r = r_buf_read_at (buf, 0, tmp, sizeof (tmp));
	if (r < sizeof (tmp)) {
		return false;
	}
	// Non-extended opcode dex file
	if (!memcmp (tmp, "dex\n035\0", 8)) {
		return true;
	}
	// Extended (jumnbo) opcode dex file, ICS+ only (sdk level 14+)
	if (!memcmp (tmp, "dex\n036\0", 8)) {
		return true;
	}
	// Two new opcodes: invoke-polymorphic and invoke-custom (sdk level 26+)
	if (!memcmp (tmp, "dex\n038\0", 8)) {
		return true;
	}
	// M3 (Nov-Dec 07)
	if (!memcmp (tmp, "dex\n009\0", 8)) {
		return true;
	}
	// M5 (Feb-Mar 08)
	if (!memcmp (tmp, "dex\n009\0", 8)) {
		return true;
	}
	// Default fall through, should still be a dex file
	if (!memcmp (tmp, "dex\n", 4)) {
		return true;
	}
	return false;
}