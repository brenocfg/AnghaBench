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
typedef  int u32 ;
struct iwl_fw_cscheme_list {int size; struct iwl_fw_cipher_scheme* cs; } ;
struct iwl_fw_cipher_scheme {int /*<<< orphan*/  cipher; } ;
struct iwl_fw {struct iwl_fw_cipher_scheme* cs; } ;

/* Variables and functions */
 int EINVAL ; 
 int IWL_UCODE_MAX_CS ; 

__attribute__((used)) static int iwl_store_cscheme(struct iwl_fw *fw, const u8 *data, const u32 len)
{
	int i, j;
	struct iwl_fw_cscheme_list *l = (struct iwl_fw_cscheme_list *)data;
	struct iwl_fw_cipher_scheme *fwcs;

	if (len < sizeof(*l) ||
	    len < sizeof(l->size) + l->size * sizeof(l->cs[0]))
		return -EINVAL;

	for (i = 0, j = 0; i < IWL_UCODE_MAX_CS && i < l->size; i++) {
		fwcs = &l->cs[j];

		/* we skip schemes with zero cipher suite selector */
		if (!fwcs->cipher)
			continue;

		fw->cs[j++] = *fwcs;
	}

	return 0;
}