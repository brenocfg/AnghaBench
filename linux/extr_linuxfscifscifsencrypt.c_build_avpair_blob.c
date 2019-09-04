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
struct ntlmssp2_name {void* length; void* type; } ;
struct nls_table {int dummy; } ;
struct TYPE_2__ {unsigned int len; unsigned char* response; } ;
struct cifs_ses {int /*<<< orphan*/  domainName; TYPE_1__ auth_key; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NTLMSSP_AV_NB_DOMAIN_NAME ; 
 int /*<<< orphan*/  cifs_strtoUTF16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,struct nls_table const*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 unsigned char* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
build_avpair_blob(struct cifs_ses *ses, const struct nls_table *nls_cp)
{
	unsigned int dlen;
	unsigned int size = 2 * sizeof(struct ntlmssp2_name);
	char *defdmname = "WORKGROUP";
	unsigned char *blobptr;
	struct ntlmssp2_name *attrptr;

	if (!ses->domainName) {
		ses->domainName = kstrdup(defdmname, GFP_KERNEL);
		if (!ses->domainName)
			return -ENOMEM;
	}

	dlen = strlen(ses->domainName);

	/*
	 * The length of this blob is two times the size of a
	 * structure (av pair) which holds name/size
	 * ( for NTLMSSP_AV_NB_DOMAIN_NAME followed by NTLMSSP_AV_EOL ) +
	 * unicode length of a netbios domain name
	 */
	ses->auth_key.len = size + 2 * dlen;
	ses->auth_key.response = kzalloc(ses->auth_key.len, GFP_KERNEL);
	if (!ses->auth_key.response) {
		ses->auth_key.len = 0;
		return -ENOMEM;
	}

	blobptr = ses->auth_key.response;
	attrptr = (struct ntlmssp2_name *) blobptr;

	/*
	 * As defined in MS-NTLM 3.3.2, just this av pair field
	 * is sufficient as part of the temp
	 */
	attrptr->type = cpu_to_le16(NTLMSSP_AV_NB_DOMAIN_NAME);
	attrptr->length = cpu_to_le16(2 * dlen);
	blobptr = (unsigned char *)attrptr + sizeof(struct ntlmssp2_name);
	cifs_strtoUTF16((__le16 *)blobptr, ses->domainName, dlen, nls_cp);

	return 0;
}