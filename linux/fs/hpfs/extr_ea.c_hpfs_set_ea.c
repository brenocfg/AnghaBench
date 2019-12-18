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
struct super_block {int dummy; } ;
struct inode {scalar_t__ i_ino; struct super_block* i_sb; } ;
struct fnode {void* ea_size_l; void* ea_secno; int /*<<< orphan*/  flags; void* ea_size_s; void* acl_size_s; void* ea_offs; } ;
struct extended_attribute {int namelen; int valuelen_lo; int valuelen_hi; int /*<<< orphan*/  name; } ;
struct buffer_head {int dummy; } ;
typedef  int secno ;
typedef  scalar_t__ fnode_secno ;
struct TYPE_2__ {int i_ea_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FNODE_anode ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  ea_data (struct extended_attribute*) ; 
 int /*<<< orphan*/  ea_in_anode (struct extended_attribute*) ; 
 scalar_t__ ea_indirect (struct extended_attribute*) ; 
 int ea_len (struct extended_attribute*) ; 
 int /*<<< orphan*/  ea_sec (struct extended_attribute*) ; 
 int ea_valuelen (struct extended_attribute*) ; 
 struct extended_attribute* fnode_ea (struct fnode*) ; 
 struct extended_attribute* fnode_end_ea (struct fnode*) ; 
 int fnode_in_anode (struct fnode*) ; 
 int hpfs_add_sector_to_btree (struct super_block*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ hpfs_alloc_if_possible (struct super_block*,int) ; 
 int hpfs_alloc_sector (struct super_block*,scalar_t__,int,int) ; 
 scalar_t__ hpfs_ea_read (struct super_block*,int,int,unsigned int,int,char*) ; 
 scalar_t__ hpfs_ea_write (struct super_block*,int,int,int,int,...) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,...) ; 
 int /*<<< orphan*/  hpfs_free_sectors (struct super_block*,int,int) ; 
 void* hpfs_get_sector (struct super_block*,int,struct buffer_head**) ; 
 TYPE_1__* hpfs_i (struct inode*) ; 
 void* hpfs_map_sector (struct super_block*,int,struct buffer_head**,int) ; 
 int /*<<< orphan*/  hpfs_truncate_btree (struct super_block*,int,int,int) ; 
 unsigned int le16_to_cpu (void*) ; 
 int le32_to_cpu (void*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 struct extended_attribute* next_ea (struct extended_attribute*) ; 
 int /*<<< orphan*/  set_indirect_ea (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int strlen (char const*) ; 

void hpfs_set_ea(struct inode *inode, struct fnode *fnode, const char *key,
		 const char *data, int size)
{
	fnode_secno fno = inode->i_ino;
	struct super_block *s = inode->i_sb;
	unsigned pos;
	int ano, len;
	secno a;
	unsigned char h[4];
	struct extended_attribute *ea;
	struct extended_attribute *ea_end = fnode_end_ea(fnode);
	for (ea = fnode_ea(fnode); ea < ea_end; ea = next_ea(ea))
		if (!strcmp(ea->name, key)) {
			if (ea_indirect(ea)) {
				if (ea_len(ea) == size)
					set_indirect_ea(s, ea_in_anode(ea), ea_sec(ea), data, size);
			} else if (ea_valuelen(ea) == size) {
				memcpy(ea_data(ea), data, size);
			}
			return;
		}
	a = le32_to_cpu(fnode->ea_secno);
	len = le32_to_cpu(fnode->ea_size_l);
	ano = fnode_in_anode(fnode);
	pos = 0;
	while (pos < len) {
		char ex[4 + 255 + 1 + 8];
		ea = (struct extended_attribute *)ex;
		if (pos + 4 > len) {
			hpfs_error(s, "EAs don't end correctly, %s %08x, len %08x",
				ano ? "anode" : "sectors", a, len);
			return;
		}
		if (hpfs_ea_read(s, a, ano, pos, 4, ex)) return;
		if (hpfs_ea_read(s, a, ano, pos + 4, ea->namelen + 1 + (ea_indirect(ea) ? 8 : 0), ex + 4))
			return;
		if (!strcmp(ea->name, key)) {
			if (ea_indirect(ea)) {
				if (ea_len(ea) == size)
					set_indirect_ea(s, ea_in_anode(ea), ea_sec(ea), data, size);
			}
			else {
				if (ea_valuelen(ea) == size)
					hpfs_ea_write(s, a, ano, pos + 4 + ea->namelen + 1, size, data);
			}
			return;
		}
		pos += ea->namelen + ea_valuelen(ea) + 5;
	}
	if (!le16_to_cpu(fnode->ea_offs)) {
		/*if (le16_to_cpu(fnode->ea_size_s)) {
			hpfs_error(s, "fnode %08x: ea_size_s == %03x, ea_offs == 0",
				inode->i_ino, le16_to_cpu(fnode->ea_size_s));
			return;
		}*/
		fnode->ea_offs = cpu_to_le16(0xc4);
	}
	if (le16_to_cpu(fnode->ea_offs) < 0xc4 || le16_to_cpu(fnode->ea_offs) + le16_to_cpu(fnode->acl_size_s) + le16_to_cpu(fnode->ea_size_s) > 0x200) {
		hpfs_error(s, "fnode %08lx: ea_offs == %03x, ea_size_s == %03x",
			(unsigned long)inode->i_ino,
			le16_to_cpu(fnode->ea_offs), le16_to_cpu(fnode->ea_size_s));
		return;
	}
	if ((le16_to_cpu(fnode->ea_size_s) || !le32_to_cpu(fnode->ea_size_l)) &&
	     le16_to_cpu(fnode->ea_offs) + le16_to_cpu(fnode->acl_size_s) + le16_to_cpu(fnode->ea_size_s) + strlen(key) + size + 5 <= 0x200) {
		ea = fnode_end_ea(fnode);
		*(char *)ea = 0;
		ea->namelen = strlen(key);
		ea->valuelen_lo = size;
		ea->valuelen_hi = size >> 8;
		strcpy(ea->name, key);
		memcpy(ea_data(ea), data, size);
		fnode->ea_size_s = cpu_to_le16(le16_to_cpu(fnode->ea_size_s) + strlen(key) + size + 5);
		goto ret;
	}
	/* Most the code here is 99.9993422% unused. I hope there are no bugs.
	   But what .. HPFS.IFS has also bugs in ea management. */
	if (le16_to_cpu(fnode->ea_size_s) && !le32_to_cpu(fnode->ea_size_l)) {
		secno n;
		struct buffer_head *bh;
		char *data;
		if (!(n = hpfs_alloc_sector(s, fno, 1, 0))) return;
		if (!(data = hpfs_get_sector(s, n, &bh))) {
			hpfs_free_sectors(s, n, 1);
			return;
		}
		memcpy(data, fnode_ea(fnode), le16_to_cpu(fnode->ea_size_s));
		fnode->ea_size_l = cpu_to_le32(le16_to_cpu(fnode->ea_size_s));
		fnode->ea_size_s = cpu_to_le16(0);
		fnode->ea_secno = cpu_to_le32(n);
		fnode->flags &= ~FNODE_anode;
		mark_buffer_dirty(bh);
		brelse(bh);
	}
	pos = le32_to_cpu(fnode->ea_size_l) + 5 + strlen(key) + size;
	len = (le32_to_cpu(fnode->ea_size_l) + 511) >> 9;
	if (pos >= 30000) goto bail;
	while (((pos + 511) >> 9) > len) {
		if (!len) {
			secno q = hpfs_alloc_sector(s, fno, 1, 0);
			if (!q) goto bail;
			fnode->ea_secno = cpu_to_le32(q);
			fnode->flags &= ~FNODE_anode;
			len++;
		} else if (!fnode_in_anode(fnode)) {
			if (hpfs_alloc_if_possible(s, le32_to_cpu(fnode->ea_secno) + len)) {
				len++;
			} else {
				/* Aargh... don't know how to create ea anodes :-( */
				/*struct buffer_head *bh;
				struct anode *anode;
				anode_secno a_s;
				if (!(anode = hpfs_alloc_anode(s, fno, &a_s, &bh)))
					goto bail;
				anode->up = cpu_to_le32(fno);
				anode->btree.fnode_parent = 1;
				anode->btree.n_free_nodes--;
				anode->btree.n_used_nodes++;
				anode->btree.first_free = cpu_to_le16(le16_to_cpu(anode->btree.first_free) + 12);
				anode->u.external[0].disk_secno = cpu_to_le32(le32_to_cpu(fnode->ea_secno));
				anode->u.external[0].file_secno = cpu_to_le32(0);
				anode->u.external[0].length = cpu_to_le32(len);
				mark_buffer_dirty(bh);
				brelse(bh);
				fnode->flags |= FNODE_anode;
				fnode->ea_secno = cpu_to_le32(a_s);*/
				secno new_sec;
				int i;
				if (!(new_sec = hpfs_alloc_sector(s, fno, 1, 1 - ((pos + 511) >> 9))))
					goto bail;
				for (i = 0; i < len; i++) {
					struct buffer_head *bh1, *bh2;
					void *b1, *b2;
					if (!(b1 = hpfs_map_sector(s, le32_to_cpu(fnode->ea_secno) + i, &bh1, len - i - 1))) {
						hpfs_free_sectors(s, new_sec, (pos + 511) >> 9);
						goto bail;
					}
					if (!(b2 = hpfs_get_sector(s, new_sec + i, &bh2))) {
						brelse(bh1);
						hpfs_free_sectors(s, new_sec, (pos + 511) >> 9);
						goto bail;
					}
					memcpy(b2, b1, 512);
					brelse(bh1);
					mark_buffer_dirty(bh2);
					brelse(bh2);
				}
				hpfs_free_sectors(s, le32_to_cpu(fnode->ea_secno), len);
				fnode->ea_secno = cpu_to_le32(new_sec);
				len = (pos + 511) >> 9;
			}
		}
		if (fnode_in_anode(fnode)) {
			if (hpfs_add_sector_to_btree(s, le32_to_cpu(fnode->ea_secno),
						     0, len) != -1) {
				len++;
			} else {
				goto bail;
			}
		}
	}
	h[0] = 0;
	h[1] = strlen(key);
	h[2] = size & 0xff;
	h[3] = size >> 8;
	if (hpfs_ea_write(s, le32_to_cpu(fnode->ea_secno), fnode_in_anode(fnode), le32_to_cpu(fnode->ea_size_l), 4, h)) goto bail;
	if (hpfs_ea_write(s, le32_to_cpu(fnode->ea_secno), fnode_in_anode(fnode), le32_to_cpu(fnode->ea_size_l) + 4, h[1] + 1, key)) goto bail;
	if (hpfs_ea_write(s, le32_to_cpu(fnode->ea_secno), fnode_in_anode(fnode), le32_to_cpu(fnode->ea_size_l) + 5 + h[1], size, data)) goto bail;
	fnode->ea_size_l = cpu_to_le32(pos);
	ret:
	hpfs_i(inode)->i_ea_size += 5 + strlen(key) + size;
	return;
	bail:
	if (le32_to_cpu(fnode->ea_secno))
		if (fnode_in_anode(fnode)) hpfs_truncate_btree(s, le32_to_cpu(fnode->ea_secno), 1, (le32_to_cpu(fnode->ea_size_l) + 511) >> 9);
		else hpfs_free_sectors(s, le32_to_cpu(fnode->ea_secno) + ((le32_to_cpu(fnode->ea_size_l) + 511) >> 9), len - ((le32_to_cpu(fnode->ea_size_l) + 511) >> 9));
	else fnode->ea_secno = fnode->ea_size_l = cpu_to_le32(0);
}