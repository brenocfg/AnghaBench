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
typedef  int /*<<< orphan*/  wpwd ;
struct nls_table {int dummy; } ;
typedef  scalar_t__ __le16 ;

/* Variables and functions */
 int cifs_strtoUTF16 (scalar_t__*,unsigned char const*,int,struct nls_table const*) ; 
 int mdfour (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memzero_explicit (scalar_t__*,int) ; 

int
E_md4hash(const unsigned char *passwd, unsigned char *p16,
	const struct nls_table *codepage)
{
	int rc;
	int len;
	__le16 wpwd[129];

	/* Password cannot be longer than 128 characters */
	if (passwd) /* Password must be converted to NT unicode */
		len = cifs_strtoUTF16(wpwd, passwd, 128, codepage);
	else {
		len = 0;
		*wpwd = 0; /* Ensure string is null terminated */
	}

	rc = mdfour(p16, (unsigned char *) wpwd, len * sizeof(__le16));
	memzero_explicit(wpwd, sizeof(wpwd));

	return rc;
}