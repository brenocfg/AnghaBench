#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut64 ;
typedef  int /*<<< orphan*/  buf2 ;
struct TYPE_4__ {int (* is_valid_offset ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int (* read_at ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  io; } ;
struct TYPE_5__ {TYPE_1__ iob; } ;
typedef  TYPE_1__ RIOBind ;
typedef  TYPE_2__ RAnal ;

/* Variables and functions */
 scalar_t__ is_invalid (int /*<<< orphan*/ *,int) ; 
 int r_mem_get_num (int /*<<< orphan*/  const*,int) ; 
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ut64 is_pointer(RAnal *anal, const ut8 *buf, int size) {
	ut64 n;
	ut8 buf2[32];
	RIOBind *iob = &anal->iob;
	if (size > sizeof (buf2)) {
		size = sizeof (buf2);
	}
	n = r_mem_get_num (buf, size);
	if (!n) {
		return 1; // null pointer
	}
#if USE_IS_VALID_OFFSET
	int r = iob->is_valid_offset (iob->io, n, 0);
	return r? n: 0LL;
#else
	// optimization to ignore very low and very high pointers
	// this makes disasm 5x faster, but can result in some false positives
	// we should compare with current offset, to avoid
	// short/long references. and discard invalid ones
	if (n < 0x1000) return 0;	// probably wrong
	if (n > 0xffffffffffffLL) return 0; // probably wrong

	if (iob->read_at (iob->io, n, buf2, size) != size) return 0;
	return is_invalid (buf2, size)? 0: n;
#endif
}