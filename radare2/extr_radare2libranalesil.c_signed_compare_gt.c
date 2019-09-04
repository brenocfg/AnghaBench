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
typedef  int /*<<< orphan*/  st8 ;
typedef  int /*<<< orphan*/  st64 ;
typedef  int /*<<< orphan*/  st32 ;
typedef  int /*<<< orphan*/  st16 ;

/* Variables and functions */

__attribute__((used)) static int signed_compare_gt(ut64 a, ut64 b, ut64 size) {
	int result;
	switch (size) {
	case 1:  result = (a & 1) > (b & 1);
		break;
	case 8:  result = (st8) a > (st8) b;
		break;
	case 16: result = (st16) a > (st16) b;
		break;
	case 32: result = (st32) a > (st32) b;
		break;
	case 64:
	default: result = (st64) a > (st64) b;
		break;
	}
	return result;
}