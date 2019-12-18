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
typedef  scalar_t__ wchar_t ;
struct msdos_dir_slot {unsigned char id; unsigned char alias_checksum; scalar_t__ attr; int /*<<< orphan*/  name11_12; int /*<<< orphan*/  name5_10; int /*<<< orphan*/  name0_4; } ;
struct msdos_dir_entry {scalar_t__* name; scalar_t__ attr; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 scalar_t__ ATTR_EXT ; 
 int ATTR_VOLUME ; 
 scalar_t__ DELETED_FLAG ; 
 int ENOMEM ; 
 scalar_t__ IS_FREE (scalar_t__*) ; 
 int PARSE_EOF ; 
 int PARSE_INVALID ; 
 int PARSE_NOT_LONGNAME ; 
 scalar_t__* __getname () ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  fat16_towchar (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 unsigned char fat_checksum (scalar_t__*) ; 
 scalar_t__ fat_get_entry (struct inode*,int /*<<< orphan*/ *,struct buffer_head**,struct msdos_dir_entry**) ; 

__attribute__((used)) static int fat_parse_long(struct inode *dir, loff_t *pos,
			  struct buffer_head **bh, struct msdos_dir_entry **de,
			  wchar_t **unicode, unsigned char *nr_slots)
{
	struct msdos_dir_slot *ds;
	unsigned char id, slot, slots, alias_checksum;

	if (!*unicode) {
		*unicode = __getname();
		if (!*unicode) {
			brelse(*bh);
			return -ENOMEM;
		}
	}
parse_long:
	ds = (struct msdos_dir_slot *)*de;
	id = ds->id;
	if (!(id & 0x40))
		return PARSE_INVALID;
	slots = id & ~0x40;
	if (slots > 20 || !slots)	/* ceil(256 * 2 / 26) */
		return PARSE_INVALID;
	*nr_slots = slots;
	alias_checksum = ds->alias_checksum;

	slot = slots;
	while (1) {
		int offset;

		slot--;
		offset = slot * 13;
		fat16_towchar(*unicode + offset, ds->name0_4, 5);
		fat16_towchar(*unicode + offset + 5, ds->name5_10, 6);
		fat16_towchar(*unicode + offset + 11, ds->name11_12, 2);

		if (ds->id & 0x40)
			(*unicode)[offset + 13] = 0;
		if (fat_get_entry(dir, pos, bh, de) < 0)
			return PARSE_EOF;
		if (slot == 0)
			break;
		ds = (struct msdos_dir_slot *)*de;
		if (ds->attr != ATTR_EXT)
			return PARSE_NOT_LONGNAME;
		if ((ds->id & ~0x40) != slot)
			goto parse_long;
		if (ds->alias_checksum != alias_checksum)
			goto parse_long;
	}
	if ((*de)->name[0] == DELETED_FLAG)
		return PARSE_INVALID;
	if ((*de)->attr == ATTR_EXT)
		goto parse_long;
	if (IS_FREE((*de)->name) || ((*de)->attr & ATTR_VOLUME))
		return PARSE_INVALID;
	if (fat_checksum((*de)->name) != alias_checksum)
		*nr_slots = 0;

	return 0;
}