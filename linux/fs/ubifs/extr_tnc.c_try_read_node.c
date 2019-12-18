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
typedef  void* uint32_t ;
struct ubifs_zbranch {int len; int lnum; int offs; int /*<<< orphan*/  hash; } ;
struct ubifs_info {scalar_t__ remounting_rw; scalar_t__ mounting; int /*<<< orphan*/  no_chk_data_crc; } ;
struct ubifs_ch {int node_type; int /*<<< orphan*/  crc; int /*<<< orphan*/  len; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  UBIFS_CRC32_INIT ; 
 int UBIFS_DATA_NODE ; 
 void* UBIFS_NODE_MAGIC ; 
 void* crc32 (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  dbg_io (char*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dbg_ntype (int) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_bad_hash (struct ubifs_info const*,void*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info const*,char*,int,int,int,int) ; 
 int ubifs_leb_read (struct ubifs_info const*,int,void*,int,int,int) ; 
 int ubifs_node_check_hash (struct ubifs_info const*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int try_read_node(const struct ubifs_info *c, void *buf, int type,
			 struct ubifs_zbranch *zbr)
{
	int len = zbr->len;
	int lnum = zbr->lnum;
	int offs = zbr->offs;
	int err, node_len;
	struct ubifs_ch *ch = buf;
	uint32_t crc, node_crc;

	dbg_io("LEB %d:%d, %s, length %d", lnum, offs, dbg_ntype(type), len);

	err = ubifs_leb_read(c, lnum, buf, offs, len, 1);
	if (err) {
		ubifs_err(c, "cannot read node type %d from LEB %d:%d, error %d",
			  type, lnum, offs, err);
		return err;
	}

	if (le32_to_cpu(ch->magic) != UBIFS_NODE_MAGIC)
		return 0;

	if (ch->node_type != type)
		return 0;

	node_len = le32_to_cpu(ch->len);
	if (node_len != len)
		return 0;

	if (type != UBIFS_DATA_NODE || !c->no_chk_data_crc || c->mounting ||
	    c->remounting_rw) {
		crc = crc32(UBIFS_CRC32_INIT, buf + 8, node_len - 8);
		node_crc = le32_to_cpu(ch->crc);
		if (crc != node_crc)
			return 0;
	}

	err = ubifs_node_check_hash(c, buf, zbr->hash);
	if (err) {
		ubifs_bad_hash(c, buf, zbr->hash, lnum, offs);
		return 0;
	}

	return 1;
}