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
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
typedef  scalar_t__ ut32 ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ RBinFile ;

/* Variables and functions */
 int r_buf_read_at (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ r_read_le32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ut64 size(RBinFile *bf) {
	ut8 u32s[sizeof (ut32)] = {0};

	int ret = r_buf_read_at (bf->buf, 108, u32s, 4);
	if (ret != 4) {
		return 0;
	}
	ut32 off = r_read_le32 (u32s);
	ret = r_buf_read_at (bf->buf, 104, u32s, 4);
	if (ret != 4) {
		return 0;
	}
	return off + r_read_le32 (u32s);
}