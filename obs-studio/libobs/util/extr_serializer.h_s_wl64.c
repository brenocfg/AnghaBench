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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct serializer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  s_wl32 (struct serializer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void s_wl64(struct serializer *s, uint64_t u64)
{
	s_wl32(s, (uint32_t)u64);
	s_wl32(s, (uint32_t)(u64 >> 32));
}