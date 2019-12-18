#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int /*<<< orphan*/  digest; } ;
struct TYPE_5__ {int nr_allocated_banks; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_DIGEST_SIZE ; 
 TYPE_2__* digests ; 
 TYPE_1__* ima_tpm_chip ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int tpm_pcr_extend (TYPE_1__*,int,TYPE_2__*) ; 

__attribute__((used)) static int ima_pcr_extend(const u8 *hash, int pcr)
{
	int result = 0;
	int i;

	if (!ima_tpm_chip)
		return result;

	for (i = 0; i < ima_tpm_chip->nr_allocated_banks; i++)
		memcpy(digests[i].digest, hash, TPM_DIGEST_SIZE);

	result = tpm_pcr_extend(ima_tpm_chip, pcr, digests);
	if (result != 0)
		pr_err("Error Communicating to TPM chip, result: %d\n", result);
	return result;
}