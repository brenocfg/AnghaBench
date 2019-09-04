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
struct switchtec_ntb {int peer_nr_direct_mw; int peer_nr_lut_mw; int nr_rsvd_luts; } ;
struct ntb_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int NTB_DEF_PEER_IDX ; 
 struct switchtec_ntb* ntb_sndev (struct ntb_dev*) ; 
 int /*<<< orphan*/  use_lut_mws ; 

__attribute__((used)) static int switchtec_ntb_mw_count(struct ntb_dev *ntb, int pidx)
{
	struct switchtec_ntb *sndev = ntb_sndev(ntb);
	int nr_direct_mw = sndev->peer_nr_direct_mw;
	int nr_lut_mw = sndev->peer_nr_lut_mw - sndev->nr_rsvd_luts;

	if (pidx != NTB_DEF_PEER_IDX)
		return -EINVAL;

	if (!use_lut_mws)
		nr_lut_mw = 0;

	return nr_direct_mw + nr_lut_mw;
}