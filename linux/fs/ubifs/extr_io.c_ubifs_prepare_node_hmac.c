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
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ubifs_crc_node (struct ubifs_info*,void*,int) ; 
 int /*<<< orphan*/  ubifs_init_node (struct ubifs_info*,void*,int,int) ; 
 int ubifs_node_insert_hmac (struct ubifs_info*,void*,int,int) ; 

int ubifs_prepare_node_hmac(struct ubifs_info *c, void *node, int len,
			    int hmac_offs, int pad)
{
	int err;

	ubifs_init_node(c, node, len, pad);

	if (hmac_offs > 0) {
		err = ubifs_node_insert_hmac(c, node, len, hmac_offs);
		if (err)
			return err;
	}

	ubifs_crc_node(c, node, len);

	return 0;
}