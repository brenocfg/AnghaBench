#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_3__ {int* p; } ;
typedef  TYPE_1__ ulebr ;
typedef  int st64 ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 

__attribute__((used)) static st64 read_sleb128(ulebr *r, ut8 *end) {
	st64 result = 0;
	int bit = 0;
	ut8 byte = 0;
	ut8 *p = r->p;
	do {
		if (p == end) {
			eprintf ("malformed sleb128\n");
			break;
		}
		byte = *p++;
		result |= (((st64)(byte & 0x7f)) << bit);
		bit += 7;
		if (bit > 63) {
			eprintf ("too large sleb128 shift\n");
			return result;
		}
	} while (byte & 0x80);
	// sign extend negative numbers
	if ((byte & 0x40)) {
		result |= (-1LL) << bit;
	}
	r->p = p;
	return result;
}