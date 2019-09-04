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
typedef  int ut32 ;
typedef  int ut16 ;
typedef  int st16 ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 int r_read_ble16 (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static bool checkEntrypoint(const ut8 *buf, ut64 length) {
	st16 cs = r_read_ble16 (buf + 0x16, false);
	ut16 ip = r_read_ble16 (buf + 0x14, false);
	ut32 pa = ((r_read_ble16 (buf + 8, false) + cs) << 4) + ip;

	/* A minimal MZ header is 0x1B bytes.  Header length is measured in
	 * 16-byte paragraphs so the minimum header must occupy 2 paragraphs.
	 * This means that the entrypoint should be at least 0x20 unless someone
	 * cleverly fit a few instructions inside the header.
	 */
	pa &= 0xffff;
	if (pa >= 0x20 && pa + 1 < length) {
		ut16 pe = r_read_ble16 (buf + 0x3c, false);
		if (pe + 2 < length && length > 0x104 && !memcmp (buf + pe, "PE", 2)) {
			return false;
		}
		return true;
	}
	return false;
}