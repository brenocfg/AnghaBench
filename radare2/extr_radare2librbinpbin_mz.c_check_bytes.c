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
typedef  int ut16 ;

/* Variables and functions */
 int /*<<< orphan*/  checkEntrypoint (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  knownHeader (int /*<<< orphan*/  const*,int,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 int r_read_ble16 (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static bool check_bytes(const ut8 *buf, ut64 length) {
	ut16 new_exe_header_offset;
	if (!buf || length <= 0x3d) {
		return false;
	}

	// Check for MZ magic.
	if (memcmp (buf, "MZ", 2) && memcmp (buf, "ZM", 2)) {
		return false;
	}

	// See if there is a new exe header.
	new_exe_header_offset = r_read_ble16 (buf + 0x3c, false);
	if (length > new_exe_header_offset + 2) {
		if (!knownHeader (buf,new_exe_header_offset, length)) {
			return false;
		}
	}

	// Raw plain MZ executable (watcom)
	if (!checkEntrypoint (buf, length)) {
		return false;
	}

	return true;
}