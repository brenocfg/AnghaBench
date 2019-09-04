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
struct tb_ctl {int (* callback ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t) ;int /*<<< orphan*/  callback_data; } ;
struct ctl_pkg {int /*<<< orphan*/  buffer; } ;
typedef  enum tb_cfg_pkg_type { ____Placeholder_tb_cfg_pkg_type } tb_cfg_pkg_type ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static bool tb_ctl_handle_event(struct tb_ctl *ctl, enum tb_cfg_pkg_type type,
				struct ctl_pkg *pkg, size_t size)
{
	return ctl->callback(ctl->callback_data, type, pkg->buffer, size);
}