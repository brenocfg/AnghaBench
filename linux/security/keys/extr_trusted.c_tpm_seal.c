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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct tpm_digests {unsigned char* xorwork; unsigned char const* xorhash; unsigned char const* nonceodd; unsigned char* encauth; unsigned char const* pubauth; } ;
struct tpm_buf {scalar_t__ data; } ;
struct osapsess {int handle; scalar_t__ secret; scalar_t__ enonce; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_BUF (struct tpm_buf*) ; 
 int LOAD32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MAX_BUF_SIZE ; 
 int SHA1_DIGEST_SIZE ; 
 scalar_t__ TPM_DATA_OFFSET ; 
 int TPM_NONCE_SIZE ; 
 int TPM_ORD_SEAL ; 
 int TPM_SEAL_SIZE ; 
 int /*<<< orphan*/  TPM_TAG_RQU_AUTH1_COMMAND ; 
 int TSS_authhmac (unsigned char const*,scalar_t__,int,scalar_t__,unsigned char const*,unsigned char,int,int*,int,unsigned char*,int,int*,int,...) ; 
 int TSS_checkhmac1 (scalar_t__,int,unsigned char const*,scalar_t__,int,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TSS_sha1 (unsigned char*,int,unsigned char const*) ; 
 int /*<<< orphan*/  chip ; 
 int /*<<< orphan*/  dump_sess (struct osapsess*) ; 
 int htonl (int) ; 
 struct tpm_digests* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct tpm_digests*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__,int) ; 
 int osap (struct tpm_buf*,struct osapsess*,unsigned char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store16 (struct tpm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store32 (struct tpm_buf*,int) ; 
 int /*<<< orphan*/  store8 (struct tpm_buf*,unsigned char) ; 
 int /*<<< orphan*/  storebytes (struct tpm_buf*,unsigned char const*,int) ; 
 int tpm_get_random (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int trusted_tpm_send (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tpm_seal(struct tpm_buf *tb, uint16_t keytype,
		    uint32_t keyhandle, const unsigned char *keyauth,
		    const unsigned char *data, uint32_t datalen,
		    unsigned char *blob, uint32_t *bloblen,
		    const unsigned char *blobauth,
		    const unsigned char *pcrinfo, uint32_t pcrinfosize)
{
	struct osapsess sess;
	struct tpm_digests *td;
	unsigned char cont;
	uint32_t ordinal;
	uint32_t pcrsize;
	uint32_t datsize;
	int sealinfosize;
	int encdatasize;
	int storedsize;
	int ret;
	int i;

	/* alloc some work space for all the hashes */
	td = kmalloc(sizeof *td, GFP_KERNEL);
	if (!td)
		return -ENOMEM;

	/* get session for sealing key */
	ret = osap(tb, &sess, keyauth, keytype, keyhandle);
	if (ret < 0)
		goto out;
	dump_sess(&sess);

	/* calculate encrypted authorization value */
	memcpy(td->xorwork, sess.secret, SHA1_DIGEST_SIZE);
	memcpy(td->xorwork + SHA1_DIGEST_SIZE, sess.enonce, SHA1_DIGEST_SIZE);
	ret = TSS_sha1(td->xorwork, SHA1_DIGEST_SIZE * 2, td->xorhash);
	if (ret < 0)
		goto out;

	ret = tpm_get_random(chip, td->nonceodd, TPM_NONCE_SIZE);
	if (ret != TPM_NONCE_SIZE)
		goto out;
	ordinal = htonl(TPM_ORD_SEAL);
	datsize = htonl(datalen);
	pcrsize = htonl(pcrinfosize);
	cont = 0;

	/* encrypt data authorization key */
	for (i = 0; i < SHA1_DIGEST_SIZE; ++i)
		td->encauth[i] = td->xorhash[i] ^ blobauth[i];

	/* calculate authorization HMAC value */
	if (pcrinfosize == 0) {
		/* no pcr info specified */
		ret = TSS_authhmac(td->pubauth, sess.secret, SHA1_DIGEST_SIZE,
				   sess.enonce, td->nonceodd, cont,
				   sizeof(uint32_t), &ordinal, SHA1_DIGEST_SIZE,
				   td->encauth, sizeof(uint32_t), &pcrsize,
				   sizeof(uint32_t), &datsize, datalen, data, 0,
				   0);
	} else {
		/* pcr info specified */
		ret = TSS_authhmac(td->pubauth, sess.secret, SHA1_DIGEST_SIZE,
				   sess.enonce, td->nonceodd, cont,
				   sizeof(uint32_t), &ordinal, SHA1_DIGEST_SIZE,
				   td->encauth, sizeof(uint32_t), &pcrsize,
				   pcrinfosize, pcrinfo, sizeof(uint32_t),
				   &datsize, datalen, data, 0, 0);
	}
	if (ret < 0)
		goto out;

	/* build and send the TPM request packet */
	INIT_BUF(tb);
	store16(tb, TPM_TAG_RQU_AUTH1_COMMAND);
	store32(tb, TPM_SEAL_SIZE + pcrinfosize + datalen);
	store32(tb, TPM_ORD_SEAL);
	store32(tb, keyhandle);
	storebytes(tb, td->encauth, SHA1_DIGEST_SIZE);
	store32(tb, pcrinfosize);
	storebytes(tb, pcrinfo, pcrinfosize);
	store32(tb, datalen);
	storebytes(tb, data, datalen);
	store32(tb, sess.handle);
	storebytes(tb, td->nonceodd, TPM_NONCE_SIZE);
	store8(tb, cont);
	storebytes(tb, td->pubauth, SHA1_DIGEST_SIZE);

	ret = trusted_tpm_send(tb->data, MAX_BUF_SIZE);
	if (ret < 0)
		goto out;

	/* calculate the size of the returned Blob */
	sealinfosize = LOAD32(tb->data, TPM_DATA_OFFSET + sizeof(uint32_t));
	encdatasize = LOAD32(tb->data, TPM_DATA_OFFSET + sizeof(uint32_t) +
			     sizeof(uint32_t) + sealinfosize);
	storedsize = sizeof(uint32_t) + sizeof(uint32_t) + sealinfosize +
	    sizeof(uint32_t) + encdatasize;

	/* check the HMAC in the response */
	ret = TSS_checkhmac1(tb->data, ordinal, td->nonceodd, sess.secret,
			     SHA1_DIGEST_SIZE, storedsize, TPM_DATA_OFFSET, 0,
			     0);

	/* copy the returned blob to caller */
	if (!ret) {
		memcpy(blob, tb->data + TPM_DATA_OFFSET, storedsize);
		*bloblen = storedsize;
	}
out:
	kzfree(td);
	return ret;
}