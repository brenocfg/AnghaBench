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
typedef  int ut32 ;

/* Variables and functions */
 int const ASN1_FORM ; 
 int const FORM_CONSTRUCTED ; 

__attribute__((used)) static ut32 asn1_ber_indefinite (const ut8 *buffer, ut32 length) {
	if (!buffer || length < 3) {
		return 0;
	}
	const ut8* next = buffer + 2;
	const ut8* end = buffer + (length - 3);
	while (next < end) {
		if (!next[0] && !next[1]) {
			break;
		}
		if (next[0] == 0x80 && (next[-1] & ASN1_FORM) == FORM_CONSTRUCTED) {
			next --;
			int sz = asn1_ber_indefinite (next, end - next);
			if (sz < 1) {
				break;
			}
			next += sz;
		}
		next ++;
	}
	return (next - buffer) + 2;
}