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
typedef  int ut64 ;
typedef  scalar_t__ ut16 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 scalar_t__ r_buf_read_le16_at (int /*<<< orphan*/ *,int) ; 
 int r_buf_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool check_buffer(RBuffer *b) {
	ut16 cksum1, cksum2;
	ut64 length = r_buf_size (b);
	// FIXME: this was commented out because it always evaluates to false.
	//        Need to be fixed by someone with SFC knowledge
	// if ((length & 0x8000) == 0x200) {
	// 	buf_hdr += 0x200;
	// }
	if (length < 0x8000) {
		return false;
	}
	//determine if ROM is headered, and add a 0x200 gap if so.
	cksum1 = r_buf_read_le16_at (b, 0x7fdc);
	cksum2 = r_buf_read_le16_at (b, 0x7fde);

	if (cksum1 == (ut16)~cksum2) {
		return true;
	}
	if (length < 0xffee) {
		return false;
	}
	cksum1 = r_buf_read_le16_at (b, 0xffdc);
	cksum2 = r_buf_read_le16_at (b, 0xffde);
	return (cksum1 == (ut16)~cksum2);
}