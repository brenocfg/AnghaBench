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
struct tap_queue {int flags; } ;

/* Variables and functions */
 int TAP_VNET_LE ; 
 scalar_t__ tap_legacy_is_little_endian (struct tap_queue*) ; 

__attribute__((used)) static inline bool tap_is_little_endian(struct tap_queue *q)
{
	return q->flags & TAP_VNET_LE ||
		tap_legacy_is_little_endian(q);
}