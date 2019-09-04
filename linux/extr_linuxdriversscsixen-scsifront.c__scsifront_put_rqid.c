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
typedef  size_t uint32_t ;
struct vscsifrnt_info {scalar_t__ wait_ring_available; int /*<<< orphan*/ ** shadow; int /*<<< orphan*/  shadow_free_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  VSCSIIF_MAX_REQS ; 
 int /*<<< orphan*/  __set_bit (size_t,int /*<<< orphan*/ ) ; 
 int bitmap_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _scsifront_put_rqid(struct vscsifrnt_info *info, uint32_t id)
{
	int empty = bitmap_empty(info->shadow_free_bitmap, VSCSIIF_MAX_REQS);

	__set_bit(id, info->shadow_free_bitmap);
	info->shadow[id] = NULL;

	return empty || info->wait_ring_available;
}