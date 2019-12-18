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
struct trusted_key_options {int /*<<< orphan*/  keyhandle; int /*<<< orphan*/  keytype; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SRKHANDLE ; 
 int /*<<< orphan*/  SRK_keytype ; 
 int /*<<< orphan*/  chip ; 
 struct trusted_key_options* kzalloc (int,int /*<<< orphan*/ ) ; 
 int tpm_is_tpm2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct trusted_key_options *trusted_options_alloc(void)
{
	struct trusted_key_options *options;
	int tpm2;

	tpm2 = tpm_is_tpm2(chip);
	if (tpm2 < 0)
		return NULL;

	options = kzalloc(sizeof *options, GFP_KERNEL);
	if (options) {
		/* set any non-zero defaults */
		options->keytype = SRK_keytype;

		if (!tpm2)
			options->keyhandle = SRKHANDLE;
	}
	return options;
}