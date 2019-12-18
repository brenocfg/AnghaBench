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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int ut32 ;
typedef  scalar_t__ st8 ;
typedef  int /*<<< orphan*/  RBuffer ;
typedef  int /*<<< orphan*/  ConsumeFcn ;

/* Variables and functions */
 int consume_r (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ read_i32_leb128 ; 

__attribute__((used)) static size_t consume_s7_r (RBuffer *b, ut64 max, st8 *out) {
	size_t n;
	ut32 tmp = consume_r (b, max, &n, (ConsumeFcn)read_i32_leb128);
	if (out) {
		*out = (st8) (((tmp & 0x10000000) << 7) | (tmp & 0x7f));
	}
	return n;
}