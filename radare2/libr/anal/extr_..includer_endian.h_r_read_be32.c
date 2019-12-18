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
typedef  scalar_t__ ut8 ;
typedef  int ut32 ;

/* Variables and functions */

__attribute__((used)) static inline ut32 r_read_be32(const void *src) {
	const ut8 *s = (const ut8*)src;
	return (((ut32)s[0]) << 24) | (((ut32)s[1]) << 16) |
		(((ut32)s[2]) << 8) | (((ut32)s[3]) << 0);
}