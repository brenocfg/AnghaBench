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
struct short_ad {void* extPosition; void* extLength; } ;

/* Variables and functions */
 void* cpu_to_le32 (void*) ; 

__attribute__((used)) static inline struct short_ad cpu_to_lesa(struct short_ad in)
{
	struct short_ad out;

	out.extLength = cpu_to_le32(in.extLength);
	out.extPosition = cpu_to_le32(in.extPosition);

	return out;
}