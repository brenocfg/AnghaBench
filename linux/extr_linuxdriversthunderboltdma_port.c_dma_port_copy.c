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
struct tb_cfg_request {int /*<<< orphan*/  response_size; int /*<<< orphan*/  response; } ;
struct ctl_pkg {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dma_port_copy(struct tb_cfg_request *req, const struct ctl_pkg *pkg)
{
	memcpy(req->response, pkg->buffer, req->response_size);
	return true;
}