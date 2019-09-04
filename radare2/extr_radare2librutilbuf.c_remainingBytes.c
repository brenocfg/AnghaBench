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
typedef  scalar_t__ ut64 ;

/* Variables and functions */
 scalar_t__ R_MIN (scalar_t__,scalar_t__) ; 

__attribute__((used)) static ut64 remainingBytes(ut64 limit, ut64 length, ut64 offset) {
	if (offset >= length ) {
		return 0;
	}
	return R_MIN (limit, length - offset);
}