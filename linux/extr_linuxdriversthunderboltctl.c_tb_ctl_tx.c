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
struct tb_ctl {int /*<<< orphan*/  tx; } ;
struct TYPE_2__ {size_t size; int sof; int eof; int /*<<< orphan*/  callback; } ;
struct ctl_pkg {TYPE_1__ frame; scalar_t__ buffer; } ;
typedef  enum tb_cfg_pkg_type { ____Placeholder_tb_cfg_pkg_type } tb_cfg_pkg_type ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int TB_FRAME_SIZE ; 
 int /*<<< orphan*/  cpu_to_be32_array (scalar_t__,void const*,size_t) ; 
 int /*<<< orphan*/  tb_crc (scalar_t__,size_t) ; 
 int /*<<< orphan*/  tb_ctl_WARN (struct tb_ctl*,char*,size_t,...) ; 
 struct ctl_pkg* tb_ctl_pkg_alloc (struct tb_ctl*) ; 
 int /*<<< orphan*/  tb_ctl_pkg_free (struct ctl_pkg*) ; 
 int /*<<< orphan*/  tb_ctl_tx_callback ; 
 int tb_ring_tx (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int tb_ctl_tx(struct tb_ctl *ctl, const void *data, size_t len,
		     enum tb_cfg_pkg_type type)
{
	int res;
	struct ctl_pkg *pkg;
	if (len % 4 != 0) { /* required for le->be conversion */
		tb_ctl_WARN(ctl, "TX: invalid size: %zu\n", len);
		return -EINVAL;
	}
	if (len > TB_FRAME_SIZE - 4) { /* checksum is 4 bytes */
		tb_ctl_WARN(ctl, "TX: packet too large: %zu/%d\n",
			    len, TB_FRAME_SIZE - 4);
		return -EINVAL;
	}
	pkg = tb_ctl_pkg_alloc(ctl);
	if (!pkg)
		return -ENOMEM;
	pkg->frame.callback = tb_ctl_tx_callback;
	pkg->frame.size = len + 4;
	pkg->frame.sof = type;
	pkg->frame.eof = type;
	cpu_to_be32_array(pkg->buffer, data, len / 4);
	*(__be32 *) (pkg->buffer + len) = tb_crc(pkg->buffer, len);

	res = tb_ring_tx(ctl->tx, &pkg->frame);
	if (res) /* ring is stopped */
		tb_ctl_pkg_free(pkg);
	return res;
}