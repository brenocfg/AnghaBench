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
typedef  int /*<<< orphan*/  ut32 ;

/* Variables and functions */
 int /*<<< orphan*/  UT32_MAX ; 
 int /*<<< orphan*/  r_read_me32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline ut32 r_read_at_me32(const void *src, size_t offset) {
	if (!src) {
		return UT32_MAX;
	}
	const ut8 *s = (const ut8*)src + offset;
	return r_read_me32 (s);
}