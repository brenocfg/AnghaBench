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
typedef  int /*<<< orphan*/  RPVector ;

/* Variables and functions */
 scalar_t__ r_pvector_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool r_pvector_empty(RPVector *vec) {
	return r_pvector_len (vec) == 0;
}