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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ima_tpm_chip ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int tpm_pcr_extend (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int ima_pcr_extend(const u8 *hash, int pcr)
{
	int result = 0;

	if (!ima_tpm_chip)
		return result;

	result = tpm_pcr_extend(ima_tpm_chip, pcr, hash);
	if (result != 0)
		pr_err("Error Communicating to TPM chip, result: %d\n", result);
	return result;
}