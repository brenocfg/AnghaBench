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
typedef  int u8 ;
struct ath6kl {scalar_t__ fw_capabilities; } ;

/* Variables and functions */
 int ATH6KL_FW_CAPABILITY_MAX ; 
 int /*<<< orphan*/  ath6kl_init_get_fw_capa_name (int) ; 
 int /*<<< orphan*/  ath6kl_warn (char*) ; 
 scalar_t__ scnprintf (char*,size_t,char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 

__attribute__((used)) static void ath6kl_init_get_fwcaps(struct ath6kl *ar, char *buf, size_t buf_len)
{
	u8 *data = (u8 *) ar->fw_capabilities;
	size_t trunc_len, len = 0;
	int i, index, bit;
	char *trunc = "...";

	for (i = 0; i < ATH6KL_FW_CAPABILITY_MAX; i++) {
		index = i / 8;
		bit = i % 8;

		if (index >= sizeof(ar->fw_capabilities) * 4)
			break;

		if (buf_len - len < 4) {
			ath6kl_warn("firmware capability buffer too small!\n");

			/* add "..." to the end of string */
			trunc_len = strlen(trunc) + 1;
			strncpy(buf + buf_len - trunc_len, trunc, trunc_len);

			return;
		}

		if (data[index] & (1 << bit)) {
			len += scnprintf(buf + len, buf_len - len, "%s,",
					    ath6kl_init_get_fw_capa_name(i));
		}
	}

	/* overwrite the last comma */
	if (len > 0)
		len--;

	buf[len] = '\0';
}