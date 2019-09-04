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
union ubifs_key {int* u32; } ;
struct ubifs_info {int key_fmt; } ;

/* Variables and functions */
#define  UBIFS_DATA_KEY 132 
#define  UBIFS_DENT_KEY 131 
#define  UBIFS_INO_KEY 130 
 int UBIFS_SIMPLE_KEY_FMT ; 
#define  UBIFS_TRUN_KEY 129 
#define  UBIFS_XENT_KEY 128 
 int /*<<< orphan*/  get_key_type (int) ; 
 int /*<<< orphan*/  key_block (struct ubifs_info const*,union ubifs_key const*) ; 
 int /*<<< orphan*/  key_hash (struct ubifs_info const*,union ubifs_key const*) ; 
 scalar_t__ key_inum (struct ubifs_info const*,union ubifs_key const*) ; 
 int key_type (struct ubifs_info const*,union ubifs_key const*) ; 
 scalar_t__ snprintf (char*,int,char*,int,...) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info const*,int) ; 

const char *dbg_snprintf_key(const struct ubifs_info *c,
			     const union ubifs_key *key, char *buffer, int len)
{
	char *p = buffer;
	int type = key_type(c, key);

	if (c->key_fmt == UBIFS_SIMPLE_KEY_FMT) {
		switch (type) {
		case UBIFS_INO_KEY:
			len -= snprintf(p, len, "(%lu, %s)",
					(unsigned long)key_inum(c, key),
					get_key_type(type));
			break;
		case UBIFS_DENT_KEY:
		case UBIFS_XENT_KEY:
			len -= snprintf(p, len, "(%lu, %s, %#08x)",
					(unsigned long)key_inum(c, key),
					get_key_type(type), key_hash(c, key));
			break;
		case UBIFS_DATA_KEY:
			len -= snprintf(p, len, "(%lu, %s, %u)",
					(unsigned long)key_inum(c, key),
					get_key_type(type), key_block(c, key));
			break;
		case UBIFS_TRUN_KEY:
			len -= snprintf(p, len, "(%lu, %s)",
					(unsigned long)key_inum(c, key),
					get_key_type(type));
			break;
		default:
			len -= snprintf(p, len, "(bad key type: %#08x, %#08x)",
					key->u32[0], key->u32[1]);
		}
	} else
		len -= snprintf(p, len, "bad key format %d", c->key_fmt);
	ubifs_assert(c, len > 0);
	return p;
}