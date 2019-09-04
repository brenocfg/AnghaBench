#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tb_cfg_request {scalar_t__ response_type; struct icm_pkg_header* request; } ;
struct icm_pkg_header {scalar_t__ code; } ;
struct TYPE_2__ {scalar_t__ eof; } ;
struct ctl_pkg {TYPE_1__ frame; struct icm_pkg_header* buffer; } ;

/* Variables and functions */

__attribute__((used)) static bool icm_match(const struct tb_cfg_request *req,
		      const struct ctl_pkg *pkg)
{
	const struct icm_pkg_header *res_hdr = pkg->buffer;
	const struct icm_pkg_header *req_hdr = req->request;

	if (pkg->frame.eof != req->response_type)
		return false;
	if (res_hdr->code != req_hdr->code)
		return false;

	return true;
}