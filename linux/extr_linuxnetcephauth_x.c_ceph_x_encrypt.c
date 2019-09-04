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
typedef  int /*<<< orphan*/  u32 ;
struct ceph_x_encrypt_header {int struct_v; int /*<<< orphan*/  magic; } ;
struct ceph_crypto_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPHX_ENC_MAGIC ; 
 int ceph_crypt (struct ceph_crypto_key*,int,void*,int,int,int*) ; 
 int /*<<< orphan*/  ceph_encode_32 (void**,int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ceph_x_encrypt(struct ceph_crypto_key *secret, void *buf,
			  int buf_len, int plaintext_len)
{
	struct ceph_x_encrypt_header *hdr = buf + sizeof(u32);
	int ciphertext_len;
	int ret;

	hdr->struct_v = 1;
	hdr->magic = cpu_to_le64(CEPHX_ENC_MAGIC);

	ret = ceph_crypt(secret, true, buf + sizeof(u32), buf_len - sizeof(u32),
			 plaintext_len + sizeof(struct ceph_x_encrypt_header),
			 &ciphertext_len);
	if (ret)
		return ret;

	ceph_encode_32(&buf, ciphertext_len);
	return sizeof(u32) + ciphertext_len;
}