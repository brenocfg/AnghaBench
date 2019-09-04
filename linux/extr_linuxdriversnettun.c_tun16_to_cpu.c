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
struct tun_struct {int dummy; } ;
typedef  int /*<<< orphan*/  __virtio16 ;

/* Variables and functions */
 int /*<<< orphan*/  __virtio16_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tun_is_little_endian (struct tun_struct*) ; 

__attribute__((used)) static inline u16 tun16_to_cpu(struct tun_struct *tun, __virtio16 val)
{
	return __virtio16_to_cpu(tun_is_little_endian(tun), val);
}