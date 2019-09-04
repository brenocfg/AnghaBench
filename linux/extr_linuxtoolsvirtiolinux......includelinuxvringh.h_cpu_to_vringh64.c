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
typedef  int /*<<< orphan*/  u64 ;
struct vringh {int dummy; } ;
typedef  int /*<<< orphan*/  __virtio64 ;

/* Variables and functions */
 int /*<<< orphan*/  __cpu_to_virtio64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vringh_is_little_endian (struct vringh const*) ; 

__attribute__((used)) static inline __virtio64 cpu_to_vringh64(const struct vringh *vrh, u64 val)
{
	return __cpu_to_virtio64(vringh_is_little_endian(vrh), val);
}