#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nls_table {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {char* release; } ;

/* Variables and functions */
 char* CIFS_NETWORK_OPSYS ; 
 int cifs_strtoUTF16 (int /*<<< orphan*/ *,char*,int,struct nls_table const*) ; 
 TYPE_1__* init_utsname () ; 

__attribute__((used)) static void
unicode_oslm_strings(char **pbcc_area, const struct nls_table *nls_cp)
{
	char *bcc_ptr = *pbcc_area;
	int bytes_ret = 0;

	/* Copy OS version */
	bytes_ret = cifs_strtoUTF16((__le16 *)bcc_ptr, "Linux version ", 32,
				    nls_cp);
	bcc_ptr += 2 * bytes_ret;
	bytes_ret = cifs_strtoUTF16((__le16 *) bcc_ptr, init_utsname()->release,
				    32, nls_cp);
	bcc_ptr += 2 * bytes_ret;
	bcc_ptr += 2; /* trailing null */

	bytes_ret = cifs_strtoUTF16((__le16 *) bcc_ptr, CIFS_NETWORK_OPSYS,
				    32, nls_cp);
	bcc_ptr += 2 * bytes_ret;
	bcc_ptr += 2; /* trailing null */

	*pbcc_area = bcc_ptr;
}