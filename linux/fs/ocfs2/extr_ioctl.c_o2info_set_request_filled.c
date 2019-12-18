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
struct ocfs2_info_request {int /*<<< orphan*/  ir_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_INFO_FL_FILLED ; 

__attribute__((used)) static inline void o2info_set_request_filled(struct ocfs2_info_request *req)
{
	req->ir_flags |= OCFS2_INFO_FL_FILLED;
}