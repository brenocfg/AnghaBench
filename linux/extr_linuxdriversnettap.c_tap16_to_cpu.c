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
typedef  int /*<<< orphan*/  u16 ;
struct tap_queue {int dummy; } ;
typedef  int /*<<< orphan*/  __virtio16 ;

/* Variables and functions */
 int /*<<< orphan*/  __virtio16_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_is_little_endian (struct tap_queue*) ; 

__attribute__((used)) static inline u16 tap16_to_cpu(struct tap_queue *q, __virtio16 val)
{
	return __virtio16_to_cpu(tap_is_little_endian(q), val);
}