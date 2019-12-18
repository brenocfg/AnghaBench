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
struct TYPE_3__ {int /*<<< orphan*/  digest; } ;
typedef  TYPE_1__ RHash ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void compare_hashes(const RHash *ctx, const ut8 *compare, int length, int *ret) {
	if (compare) {
		// algobit has only 1 bit set
		if (!memcmp (ctx->digest, compare, length)) {
			printf ("rahash2: Computed hash matches the expected one.\n");
		} else {
			eprintf ("rahash2: Computed hash doesn't match the expected one.\n");
			*ret = 1;
		}
	}
}