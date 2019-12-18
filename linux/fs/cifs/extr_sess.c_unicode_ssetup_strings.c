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
struct nls_table {int dummy; } ;
struct cifs_ses {int /*<<< orphan*/ * user_name; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_MAX_USERNAME_LEN ; 
 int cifs_strtoUTF16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nls_table const*) ; 
 int /*<<< orphan*/  unicode_domain_string (char**,struct cifs_ses*,struct nls_table const*) ; 
 int /*<<< orphan*/  unicode_oslm_strings (char**,struct nls_table const*) ; 

__attribute__((used)) static void unicode_ssetup_strings(char **pbcc_area, struct cifs_ses *ses,
				   const struct nls_table *nls_cp)
{
	char *bcc_ptr = *pbcc_area;
	int bytes_ret = 0;

	/* BB FIXME add check that strings total less
	than 335 or will need to send them as arrays */

	/* unicode strings, must be word aligned before the call */
/*	if ((long) bcc_ptr % 2)	{
		*bcc_ptr = 0;
		bcc_ptr++;
	} */
	/* copy user */
	if (ses->user_name == NULL) {
		/* null user mount */
		*bcc_ptr = 0;
		*(bcc_ptr+1) = 0;
	} else {
		bytes_ret = cifs_strtoUTF16((__le16 *) bcc_ptr, ses->user_name,
					    CIFS_MAX_USERNAME_LEN, nls_cp);
	}
	bcc_ptr += 2 * bytes_ret;
	bcc_ptr += 2; /* account for null termination */

	unicode_domain_string(&bcc_ptr, ses, nls_cp);
	unicode_oslm_strings(&bcc_ptr, nls_cp);

	*pbcc_area = bcc_ptr;
}