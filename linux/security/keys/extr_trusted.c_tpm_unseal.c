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
typedef  scalar_t__ uint32_t ;
struct tpm_buf {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_BUF (struct tpm_buf*) ; 
 unsigned int LOAD32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MAX_BUF_SIZE ; 
 int SHA1_DIGEST_SIZE ; 
 scalar_t__ SRKHANDLE ; 
 scalar_t__ TPM_DATA_OFFSET ; 
 int TPM_NONCE_SIZE ; 
 scalar_t__ TPM_ORD_UNSEAL ; 
 int /*<<< orphan*/  TPM_TAG_RQU_AUTH2_COMMAND ; 
 scalar_t__ TPM_UNSEAL_SIZE ; 
 int TSS_authhmac (unsigned char*,unsigned char const*,int,unsigned char*,unsigned char*,unsigned char,int,scalar_t__*,int,unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TSS_checkhmac2 (scalar_t__,scalar_t__,unsigned char*,unsigned char const*,int,unsigned char const*,int,int,scalar_t__,unsigned int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chip ; 
 scalar_t__ htonl (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__,unsigned int) ; 
 int oiap (struct tpm_buf*,scalar_t__*,unsigned char*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  store16 (struct tpm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store32 (struct tpm_buf*,scalar_t__) ; 
 int /*<<< orphan*/  store8 (struct tpm_buf*,unsigned char) ; 
 int /*<<< orphan*/  storebytes (struct tpm_buf*,unsigned char const*,int) ; 
 int tpm_get_random (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int trusted_tpm_send (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tpm_unseal(struct tpm_buf *tb,
		      uint32_t keyhandle, const unsigned char *keyauth,
		      const unsigned char *blob, int bloblen,
		      const unsigned char *blobauth,
		      unsigned char *data, unsigned int *datalen)
{
	unsigned char nonceodd[TPM_NONCE_SIZE];
	unsigned char enonce1[TPM_NONCE_SIZE];
	unsigned char enonce2[TPM_NONCE_SIZE];
	unsigned char authdata1[SHA1_DIGEST_SIZE];
	unsigned char authdata2[SHA1_DIGEST_SIZE];
	uint32_t authhandle1 = 0;
	uint32_t authhandle2 = 0;
	unsigned char cont = 0;
	uint32_t ordinal;
	uint32_t keyhndl;
	int ret;

	/* sessions for unsealing key and data */
	ret = oiap(tb, &authhandle1, enonce1);
	if (ret < 0) {
		pr_info("trusted_key: oiap failed (%d)\n", ret);
		return ret;
	}
	ret = oiap(tb, &authhandle2, enonce2);
	if (ret < 0) {
		pr_info("trusted_key: oiap failed (%d)\n", ret);
		return ret;
	}

	ordinal = htonl(TPM_ORD_UNSEAL);
	keyhndl = htonl(SRKHANDLE);
	ret = tpm_get_random(chip, nonceodd, TPM_NONCE_SIZE);
	if (ret != TPM_NONCE_SIZE) {
		pr_info("trusted_key: tpm_get_random failed (%d)\n", ret);
		return ret;
	}
	ret = TSS_authhmac(authdata1, keyauth, TPM_NONCE_SIZE,
			   enonce1, nonceodd, cont, sizeof(uint32_t),
			   &ordinal, bloblen, blob, 0, 0);
	if (ret < 0)
		return ret;
	ret = TSS_authhmac(authdata2, blobauth, TPM_NONCE_SIZE,
			   enonce2, nonceodd, cont, sizeof(uint32_t),
			   &ordinal, bloblen, blob, 0, 0);
	if (ret < 0)
		return ret;

	/* build and send TPM request packet */
	INIT_BUF(tb);
	store16(tb, TPM_TAG_RQU_AUTH2_COMMAND);
	store32(tb, TPM_UNSEAL_SIZE + bloblen);
	store32(tb, TPM_ORD_UNSEAL);
	store32(tb, keyhandle);
	storebytes(tb, blob, bloblen);
	store32(tb, authhandle1);
	storebytes(tb, nonceodd, TPM_NONCE_SIZE);
	store8(tb, cont);
	storebytes(tb, authdata1, SHA1_DIGEST_SIZE);
	store32(tb, authhandle2);
	storebytes(tb, nonceodd, TPM_NONCE_SIZE);
	store8(tb, cont);
	storebytes(tb, authdata2, SHA1_DIGEST_SIZE);

	ret = trusted_tpm_send(tb->data, MAX_BUF_SIZE);
	if (ret < 0) {
		pr_info("trusted_key: authhmac failed (%d)\n", ret);
		return ret;
	}

	*datalen = LOAD32(tb->data, TPM_DATA_OFFSET);
	ret = TSS_checkhmac2(tb->data, ordinal, nonceodd,
			     keyauth, SHA1_DIGEST_SIZE,
			     blobauth, SHA1_DIGEST_SIZE,
			     sizeof(uint32_t), TPM_DATA_OFFSET,
			     *datalen, TPM_DATA_OFFSET + sizeof(uint32_t), 0,
			     0);
	if (ret < 0) {
		pr_info("trusted_key: TSS_checkhmac2 failed (%d)\n", ret);
		return ret;
	}
	memcpy(data, tb->data + TPM_DATA_OFFSET + sizeof(uint32_t), *datalen);
	return 0;
}