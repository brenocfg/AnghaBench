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
struct qstr {unsigned char* name; size_t len; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct fscrypt_name {int hash; TYPE_1__ disk_name; } ;
typedef  int /*<<< orphan*/  f2fs_hash_t ;
typedef  int __u32 ;

/* Variables and functions */
 int F2FS_HASH_COL_BIT ; 
 int /*<<< orphan*/  TEA_transform (int*,int*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 scalar_t__ is_dot_dotdot (struct qstr const*) ; 
 int /*<<< orphan*/  str2hashbuf (unsigned char const*,size_t,int*,int) ; 

__attribute__((used)) static f2fs_hash_t __f2fs_dentry_hash(const struct qstr *name_info,
				struct fscrypt_name *fname)
{
	__u32 hash;
	f2fs_hash_t f2fs_hash;
	const unsigned char *p;
	__u32 in[8], buf[4];
	const unsigned char *name = name_info->name;
	size_t len = name_info->len;

	/* encrypted bigname case */
	if (fname && !fname->disk_name.name)
		return cpu_to_le32(fname->hash);

	if (is_dot_dotdot(name_info))
		return 0;

	/* Initialize the default seed for the hash checksum functions */
	buf[0] = 0x67452301;
	buf[1] = 0xefcdab89;
	buf[2] = 0x98badcfe;
	buf[3] = 0x10325476;

	p = name;
	while (1) {
		str2hashbuf(p, len, in, 4);
		TEA_transform(buf, in);
		p += 16;
		if (len <= 16)
			break;
		len -= 16;
	}
	hash = buf[0];
	f2fs_hash = cpu_to_le32(hash & ~F2FS_HASH_COL_BIT);
	return f2fs_hash;
}