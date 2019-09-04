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
struct tb_cfg_request {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_CFG_REQUEST_ACTIVE ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool tb_cfg_request_is_active(struct tb_cfg_request *req)
{
	return test_bit(TB_CFG_REQUEST_ACTIVE, &req->flags);
}