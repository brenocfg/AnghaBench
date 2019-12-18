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
typedef  char u8 ;
typedef  void* u32 ;
struct qstr {int dummy; } ;
struct inode {int dummy; } ;
struct fscrypt_str {char* name; int len; } ;
struct fscrypt_digested_name {int /*<<< orphan*/  digest; void* minor_hash; void* hash; } ;
typedef  int /*<<< orphan*/  digested_name ;

/* Variables and functions */
 int EUCLEAN ; 
 int /*<<< orphan*/  FSCRYPT_FNAME_DIGEST (char const*,int) ; 
 int /*<<< orphan*/  FSCRYPT_FNAME_DIGEST_SIZE ; 
 int FSCRYPT_FNAME_MAX_UNDIGESTED_SIZE ; 
 struct qstr FSTR_TO_QSTR (struct fscrypt_str const*) ; 
 int FS_CRYPTO_BLOCK_SIZE ; 
 void* base64_encode (char const*,int,char const*) ; 
 int fname_decrypt (struct inode*,struct fscrypt_str const*,struct fscrypt_str*) ; 
 scalar_t__ fscrypt_has_encryption_key (struct inode*) ; 
 scalar_t__ fscrypt_is_dot_dotdot (struct qstr const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int fscrypt_fname_disk_to_usr(struct inode *inode,
			u32 hash, u32 minor_hash,
			const struct fscrypt_str *iname,
			struct fscrypt_str *oname)
{
	const struct qstr qname = FSTR_TO_QSTR(iname);
	struct fscrypt_digested_name digested_name;

	if (fscrypt_is_dot_dotdot(&qname)) {
		oname->name[0] = '.';
		oname->name[iname->len - 1] = '.';
		oname->len = iname->len;
		return 0;
	}

	if (iname->len < FS_CRYPTO_BLOCK_SIZE)
		return -EUCLEAN;

	if (fscrypt_has_encryption_key(inode))
		return fname_decrypt(inode, iname, oname);

	if (iname->len <= FSCRYPT_FNAME_MAX_UNDIGESTED_SIZE) {
		oname->len = base64_encode(iname->name, iname->len,
					   oname->name);
		return 0;
	}
	if (hash) {
		digested_name.hash = hash;
		digested_name.minor_hash = minor_hash;
	} else {
		digested_name.hash = 0;
		digested_name.minor_hash = 0;
	}
	memcpy(digested_name.digest,
	       FSCRYPT_FNAME_DIGEST(iname->name, iname->len),
	       FSCRYPT_FNAME_DIGEST_SIZE);
	oname->name[0] = '_';
	oname->len = 1 + base64_encode((const u8 *)&digested_name,
				       sizeof(digested_name), oname->name + 1);
	return 0;
}