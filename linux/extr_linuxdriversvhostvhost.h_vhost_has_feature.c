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
struct vhost_virtqueue {unsigned long long acked_features; } ;

/* Variables and functions */

__attribute__((used)) static inline bool vhost_has_feature(struct vhost_virtqueue *vq, int bit)
{
	return vq->acked_features & (1ULL << bit);
}