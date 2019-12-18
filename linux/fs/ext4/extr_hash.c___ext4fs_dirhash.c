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
struct dx_hash_info {int hash_version; int hash; int minor_hash; scalar_t__* seed; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int __u32 ;

/* Variables and functions */
#define  DX_HASH_HALF_MD4 133 
#define  DX_HASH_HALF_MD4_UNSIGNED 132 
#define  DX_HASH_LEGACY 131 
#define  DX_HASH_LEGACY_UNSIGNED 130 
#define  DX_HASH_TEA 129 
#define  DX_HASH_TEA_UNSIGNED 128 
 int EXT4_HTREE_EOF_32BIT ; 
 int /*<<< orphan*/  TEA_transform (int*,int*) ; 
 int dx_hack_hash_signed (char const*,int) ; 
 int dx_hack_hash_unsigned (char const*,int) ; 
 int /*<<< orphan*/  half_md4_transform (int*,int*) ; 
 int /*<<< orphan*/  memcpy (int*,scalar_t__*,int) ; 
 void str2hashbuf_signed (char const*,int,int*,int) ; 
 void str2hashbuf_unsigned (char const*,int,int*,int) ; 
 void stub1 (char const*,int,int*,int) ; 
 void stub2 (char const*,int,int*,int) ; 

__attribute__((used)) static int __ext4fs_dirhash(const char *name, int len,
			    struct dx_hash_info *hinfo)
{
	__u32	hash;
	__u32	minor_hash = 0;
	const char	*p;
	int		i;
	__u32		in[8], buf[4];
	void		(*str2hashbuf)(const char *, int, __u32 *, int) =
				str2hashbuf_signed;

	/* Initialize the default seed for the hash checksum functions */
	buf[0] = 0x67452301;
	buf[1] = 0xefcdab89;
	buf[2] = 0x98badcfe;
	buf[3] = 0x10325476;

	/* Check to see if the seed is all zero's */
	if (hinfo->seed) {
		for (i = 0; i < 4; i++) {
			if (hinfo->seed[i]) {
				memcpy(buf, hinfo->seed, sizeof(buf));
				break;
			}
		}
	}

	switch (hinfo->hash_version) {
	case DX_HASH_LEGACY_UNSIGNED:
		hash = dx_hack_hash_unsigned(name, len);
		break;
	case DX_HASH_LEGACY:
		hash = dx_hack_hash_signed(name, len);
		break;
	case DX_HASH_HALF_MD4_UNSIGNED:
		str2hashbuf = str2hashbuf_unsigned;
		/* fall through */
	case DX_HASH_HALF_MD4:
		p = name;
		while (len > 0) {
			(*str2hashbuf)(p, len, in, 8);
			half_md4_transform(buf, in);
			len -= 32;
			p += 32;
		}
		minor_hash = buf[2];
		hash = buf[1];
		break;
	case DX_HASH_TEA_UNSIGNED:
		str2hashbuf = str2hashbuf_unsigned;
		/* fall through */
	case DX_HASH_TEA:
		p = name;
		while (len > 0) {
			(*str2hashbuf)(p, len, in, 4);
			TEA_transform(buf, in);
			len -= 16;
			p += 16;
		}
		hash = buf[0];
		minor_hash = buf[1];
		break;
	default:
		hinfo->hash = 0;
		return -1;
	}
	hash = hash & ~1;
	if (hash == (EXT4_HTREE_EOF_32BIT << 1))
		hash = (EXT4_HTREE_EOF_32BIT - 1) << 1;
	hinfo->hash = hash;
	hinfo->minor_hash = minor_hash;
	return 0;
}