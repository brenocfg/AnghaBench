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
struct ism_resp_hdr {int ret; int len; } ;
struct ism_req_hdr {int len; } ;
struct ism_dev {scalar_t__ ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISM_ERROR ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ism_resp_hdr*,int) ; 
 int /*<<< orphan*/  debug_text_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ism_debug_info ; 
 int /*<<< orphan*/  memcpy_fromio (struct ism_resp_hdr*,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,struct ism_req_hdr*,int) ; 

__attribute__((used)) static int ism_cmd(struct ism_dev *ism, void *cmd)
{
	struct ism_req_hdr *req = cmd;
	struct ism_resp_hdr *resp = cmd;

	memcpy_toio(ism->ctl + sizeof(*req), req + 1, req->len - sizeof(*req));
	memcpy_toio(ism->ctl, req, sizeof(*req));

	WRITE_ONCE(resp->ret, ISM_ERROR);

	memcpy_fromio(resp, ism->ctl, sizeof(*resp));
	if (resp->ret) {
		debug_text_event(ism_debug_info, 0, "cmd failure");
		debug_event(ism_debug_info, 0, resp, sizeof(*resp));
		goto out;
	}
	memcpy_fromio(resp + 1, ism->ctl + sizeof(*resp),
		      resp->len - sizeof(*resp));
out:
	return resp->ret;
}