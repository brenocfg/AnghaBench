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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct tpm_buf {int /*<<< orphan*/ * data; } ;
struct osapsess {unsigned char* enonce; int /*<<< orphan*/  secret; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_BUF (struct tpm_buf*) ; 
 int /*<<< orphan*/  LOAD32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MAX_BUF_SIZE ; 
 int /*<<< orphan*/  SHA1_DIGEST_SIZE ; 
 int TPM_DATA_OFFSET ; 
 int TPM_NONCE_SIZE ; 
 int /*<<< orphan*/  TPM_ORD_OSAP ; 
 int /*<<< orphan*/  TPM_OSAP_SIZE ; 
 int /*<<< orphan*/  TPM_TAG_RQU_COMMAND ; 
 int TSS_rawhmac (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ,int,unsigned char*,int,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chip ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  store16 (struct tpm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store32 (struct tpm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storebytes (struct tpm_buf*,unsigned char*,int) ; 
 int tpm_get_random (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int trusted_tpm_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int osap(struct tpm_buf *tb, struct osapsess *s,
		const unsigned char *key, uint16_t type, uint32_t handle)
{
	unsigned char enonce[TPM_NONCE_SIZE];
	unsigned char ononce[TPM_NONCE_SIZE];
	int ret;

	ret = tpm_get_random(chip, ononce, TPM_NONCE_SIZE);
	if (ret != TPM_NONCE_SIZE)
		return ret;

	INIT_BUF(tb);
	store16(tb, TPM_TAG_RQU_COMMAND);
	store32(tb, TPM_OSAP_SIZE);
	store32(tb, TPM_ORD_OSAP);
	store16(tb, type);
	store32(tb, handle);
	storebytes(tb, ononce, TPM_NONCE_SIZE);

	ret = trusted_tpm_send(tb->data, MAX_BUF_SIZE);
	if (ret < 0)
		return ret;

	s->handle = LOAD32(tb->data, TPM_DATA_OFFSET);
	memcpy(s->enonce, &(tb->data[TPM_DATA_OFFSET + sizeof(uint32_t)]),
	       TPM_NONCE_SIZE);
	memcpy(enonce, &(tb->data[TPM_DATA_OFFSET + sizeof(uint32_t) +
				  TPM_NONCE_SIZE]), TPM_NONCE_SIZE);
	return TSS_rawhmac(s->secret, key, SHA1_DIGEST_SIZE, TPM_NONCE_SIZE,
			   enonce, TPM_NONCE_SIZE, ononce, 0, 0);
}