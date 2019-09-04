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
struct cifs_ses {void* serverNOS; void* serverOS; } ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (void*,char*,int) ; 
 int /*<<< orphan*/  strncpy (void*,char*,int) ; 
 int strnlen (char*,int) ; 

__attribute__((used)) static void decode_ascii_ssetup(char **pbcc_area, __u16 bleft,
				struct cifs_ses *ses,
				const struct nls_table *nls_cp)
{
	int len;
	char *bcc_ptr = *pbcc_area;

	cifs_dbg(FYI, "decode sessetup ascii. bleft %d\n", bleft);

	len = strnlen(bcc_ptr, bleft);
	if (len >= bleft)
		return;

	kfree(ses->serverOS);

	ses->serverOS = kzalloc(len + 1, GFP_KERNEL);
	if (ses->serverOS) {
		strncpy(ses->serverOS, bcc_ptr, len);
		if (strncmp(ses->serverOS, "OS/2", 4) == 0)
			cifs_dbg(FYI, "OS/2 server\n");
	}

	bcc_ptr += len + 1;
	bleft -= len + 1;

	len = strnlen(bcc_ptr, bleft);
	if (len >= bleft)
		return;

	kfree(ses->serverNOS);

	ses->serverNOS = kzalloc(len + 1, GFP_KERNEL);
	if (ses->serverNOS)
		strncpy(ses->serverNOS, bcc_ptr, len);

	bcc_ptr += len + 1;
	bleft -= len + 1;

	len = strnlen(bcc_ptr, bleft);
	if (len > bleft)
		return;

	/* No domain field in LANMAN case. Domain is
	   returned by old servers in the SMB negprot response */
	/* BB For newer servers which do not support Unicode,
	   but thus do return domain here we could add parsing
	   for it later, but it is not very important */
	cifs_dbg(FYI, "ascii: bytes left %d\n", bleft);
}