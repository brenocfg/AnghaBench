#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct virtqueue {int dummy; } ;
struct fuse_pqueue {int dummy; } ;
struct TYPE_4__ {TYPE_1__* fud; } ;
struct TYPE_3__ {struct fuse_pqueue pq; } ;

/* Variables and functions */
 TYPE_2__* vq_to_fsvq (struct virtqueue*) ; 

__attribute__((used)) static inline struct fuse_pqueue *vq_to_fpq(struct virtqueue *vq)
{
	return &vq_to_fsvq(vq)->fud->pq;
}