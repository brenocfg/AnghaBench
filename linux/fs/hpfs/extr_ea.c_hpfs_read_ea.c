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
struct super_block {int dummy; } ;
struct fnode {int /*<<< orphan*/  ea_size_l; int /*<<< orphan*/  ea_secno; } ;
struct extended_attribute {int namelen; int /*<<< orphan*/  name; } ;
typedef  void* secno ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  ea_data (struct extended_attribute*) ; 
 int ea_in_anode (struct extended_attribute*) ; 
 scalar_t__ ea_indirect (struct extended_attribute*) ; 
 size_t ea_len (struct extended_attribute*) ; 
 void* ea_sec (struct extended_attribute*) ; 
 int ea_valuelen (struct extended_attribute*) ; 
 struct extended_attribute* fnode_ea (struct fnode*) ; 
 struct extended_attribute* fnode_end_ea (struct fnode*) ; 
 int fnode_in_anode (struct fnode*) ; 
 scalar_t__ hpfs_ea_read (struct super_block*,void*,int,unsigned int,size_t,char*) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,char*,void*,int) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 struct extended_attribute* next_ea (struct extended_attribute*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int hpfs_read_ea(struct super_block *s, struct fnode *fnode, char *key,
		char *buf, int size)
{
	unsigned pos;
	int ano, len;
	secno a;
	char ex[4 + 255 + 1 + 8];
	struct extended_attribute *ea;
	struct extended_attribute *ea_end = fnode_end_ea(fnode);
	for (ea = fnode_ea(fnode); ea < ea_end; ea = next_ea(ea))
		if (!strcmp(ea->name, key)) {
			if (ea_indirect(ea))
				goto indirect;
			if (ea_valuelen(ea) >= size)
				return -EINVAL;
			memcpy(buf, ea_data(ea), ea_valuelen(ea));
			buf[ea_valuelen(ea)] = 0;
			return 0;
		}
	a = le32_to_cpu(fnode->ea_secno);
	len = le32_to_cpu(fnode->ea_size_l);
	ano = fnode_in_anode(fnode);
	pos = 0;
	while (pos < len) {
		ea = (struct extended_attribute *)ex;
		if (pos + 4 > len) {
			hpfs_error(s, "EAs don't end correctly, %s %08x, len %08x",
				ano ? "anode" : "sectors", a, len);
			return -EIO;
		}
		if (hpfs_ea_read(s, a, ano, pos, 4, ex)) return -EIO;
		if (hpfs_ea_read(s, a, ano, pos + 4, ea->namelen + 1 + (ea_indirect(ea) ? 8 : 0), ex + 4))
			return -EIO;
		if (!strcmp(ea->name, key)) {
			if (ea_indirect(ea))
				goto indirect;
			if (ea_valuelen(ea) >= size)
				return -EINVAL;
			if (hpfs_ea_read(s, a, ano, pos + 4 + ea->namelen + 1, ea_valuelen(ea), buf))
				return -EIO;
			buf[ea_valuelen(ea)] = 0;
			return 0;
		}
		pos += ea->namelen + ea_valuelen(ea) + 5;
	}
	return -ENOENT;
indirect:
	if (ea_len(ea) >= size)
		return -EINVAL;
	if (hpfs_ea_read(s, ea_sec(ea), ea_in_anode(ea), 0, ea_len(ea), buf))
		return -EIO;
	buf[ea_len(ea)] = 0;
	return 0;
}