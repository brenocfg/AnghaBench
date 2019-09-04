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
typedef  scalar_t__ ut16 ;

/* Variables and functions */
 scalar_t__ r_read_le16 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bool check_bytes(const ut8 *buf, ut64 length) {
	const ut8 *buf_hdr = buf;
	ut16 cksum1, cksum2;

	// FIXME: this was commented out because it always evaluates to false.
	//        Need to be fixed by someone with SFC knowledge
	// if ((length & 0x8000) == 0x200) {
	// 	buf_hdr += 0x200;
	// }
	if (length < 0x8000) {
		return false;
	}
	//determine if ROM is headered, and add a 0x200 gap if so.
	cksum1 = r_read_le16 (buf_hdr + 0x7FDC);
	cksum2 = r_read_le16 (buf_hdr + 0x7FDE);

	if (cksum1 == (ut16)~cksum2) {
		return true;
	}

	if (length < 0xffee) {
		return false;
	}
	cksum1 = r_read_le16(buf_hdr + 0xFFDC);
	cksum2 = r_read_le16(buf_hdr + 0xFFDE);
	return (cksum1 == (ut16)~cksum2);
}