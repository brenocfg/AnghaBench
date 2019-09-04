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
struct request {int dummy; } ;
struct dasd_device {int dummy; } ;
struct dasd_ccw_req {int dummy; } ;
struct dasd_block {int dummy; } ;

/* Variables and functions */
 scalar_t__ REQ_OP_DISCARD ; 
 scalar_t__ REQ_OP_WRITE_ZEROES ; 
 struct dasd_ccw_req* dasd_fba_build_cp_discard (struct dasd_device*,struct dasd_block*,struct request*) ; 
 struct dasd_ccw_req* dasd_fba_build_cp_regular (struct dasd_device*,struct dasd_block*,struct request*) ; 
 scalar_t__ req_op (struct request*) ; 

__attribute__((used)) static struct dasd_ccw_req *dasd_fba_build_cp(struct dasd_device *memdev,
					      struct dasd_block *block,
					      struct request *req)
{
	if (req_op(req) == REQ_OP_DISCARD || req_op(req) == REQ_OP_WRITE_ZEROES)
		return dasd_fba_build_cp_discard(memdev, block, req);
	else
		return dasd_fba_build_cp_regular(memdev, block, req);
}