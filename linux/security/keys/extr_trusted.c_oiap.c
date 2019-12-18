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
struct tpm_buf {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  INIT_BUF (struct tpm_buf*) ; 
 int /*<<< orphan*/  LOAD32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MAX_BUF_SIZE ; 
 int TPM_DATA_OFFSET ; 
 int /*<<< orphan*/  TPM_NONCE_SIZE ; 
 int /*<<< orphan*/  TPM_OIAP_SIZE ; 
 int /*<<< orphan*/  TPM_ORD_OIAP ; 
 int /*<<< orphan*/  TPM_TAG_RQU_COMMAND ; 
 int /*<<< orphan*/  chip ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store16 (struct tpm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store32 (struct tpm_buf*,int /*<<< orphan*/ ) ; 
 int trusted_tpm_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int oiap(struct tpm_buf *tb, uint32_t *handle, unsigned char *nonce)
{
	int ret;

	if (!chip)
		return -ENODEV;

	INIT_BUF(tb);
	store16(tb, TPM_TAG_RQU_COMMAND);
	store32(tb, TPM_OIAP_SIZE);
	store32(tb, TPM_ORD_OIAP);
	ret = trusted_tpm_send(tb->data, MAX_BUF_SIZE);
	if (ret < 0)
		return ret;

	*handle = LOAD32(tb->data, TPM_DATA_OFFSET);
	memcpy(nonce, &tb->data[TPM_DATA_OFFSET + sizeof(uint32_t)],
	       TPM_NONCE_SIZE);
	return 0;
}