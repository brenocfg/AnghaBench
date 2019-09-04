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
struct vscsiif_response {unsigned int rqid; int rslt; scalar_t__ residual_len; scalar_t__ sense_len; } ;
struct vscsifrnt_info {int /*<<< orphan*/  shadow_free_bitmap; } ;

/* Variables and functions */
 int DID_RESET ; 
 unsigned int VSCSIIF_MAX_REQS ; 
 int /*<<< orphan*/  scsifront_do_response (struct vscsifrnt_info*,struct vscsiif_response*) ; 
 int /*<<< orphan*/  scsifront_ring_drain (struct vscsifrnt_info*) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scsifront_finish_all(struct vscsifrnt_info *info)
{
	unsigned i;
	struct vscsiif_response resp;

	scsifront_ring_drain(info);

	for (i = 0; i < VSCSIIF_MAX_REQS; i++) {
		if (test_bit(i, info->shadow_free_bitmap))
			continue;
		resp.rqid = i;
		resp.sense_len = 0;
		resp.rslt = DID_RESET << 16;
		resp.residual_len = 0;
		scsifront_do_response(info, &resp);
	}
}