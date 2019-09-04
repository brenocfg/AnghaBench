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
struct tb_cfg_result {int err; scalar_t__ response_port; int /*<<< orphan*/  tb_error; int /*<<< orphan*/  response_route; int /*<<< orphan*/  member_0; } ;
struct ctl_pkg {struct cfg_error_pkg* buffer; } ;
struct cfg_error_pkg {scalar_t__ port; int /*<<< orphan*/  error; int /*<<< orphan*/  zero1; int /*<<< orphan*/  zero3; int /*<<< orphan*/  zero2; int /*<<< orphan*/  header; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_CFG_PKG_ERROR ; 
 int /*<<< orphan*/  WARN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int check_header (struct ctl_pkg const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_cfg_get_route (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct tb_cfg_result decode_error(const struct ctl_pkg *response)
{
	struct cfg_error_pkg *pkg = response->buffer;
	struct tb_cfg_result res = { 0 };
	res.response_route = tb_cfg_get_route(&pkg->header);
	res.response_port = 0;
	res.err = check_header(response, sizeof(*pkg), TB_CFG_PKG_ERROR,
			       tb_cfg_get_route(&pkg->header));
	if (res.err)
		return res;

	WARN(pkg->zero1, "pkg->zero1 is %#x\n", pkg->zero1);
	WARN(pkg->zero2, "pkg->zero1 is %#x\n", pkg->zero1);
	WARN(pkg->zero3, "pkg->zero1 is %#x\n", pkg->zero1);
	res.err = 1;
	res.tb_error = pkg->error;
	res.response_port = pkg->port;
	return res;

}