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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  RHash ;

/* Variables and functions */
 int /*<<< orphan*/  _s ; 
 int /*<<< orphan*/  do_hash_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ iterations ; 
 int r_hash_calculate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  r_hash_do_spice (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_hash_internal(RHash *ctx, ut64 hash, const ut8 *buf, int len, int rad, int print, int le) {
	if (len < 0) {
		return 0;
	}
	int dlen = r_hash_calculate (ctx, hash, buf, len);
	if (!print) {
		return 1;
	}
	if (iterations > 0) {
		r_hash_do_spice (ctx, hash, iterations, _s);
	}
	do_hash_print (ctx, hash, dlen, rad, le);
	return 1;
}