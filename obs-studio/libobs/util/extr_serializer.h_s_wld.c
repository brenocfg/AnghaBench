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
typedef  int /*<<< orphan*/  uint64_t ;
struct serializer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  s_wl64 (struct serializer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void s_wld(struct serializer *s, double d)
{
	s_wl64(s, *(uint64_t *)&d);
}