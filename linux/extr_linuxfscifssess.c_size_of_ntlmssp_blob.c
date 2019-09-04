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
struct TYPE_2__ {int len; } ;
struct cifs_ses {scalar_t__ user_name; scalar_t__ domainName; TYPE_1__ auth_key; } ;
typedef  int /*<<< orphan*/  AUTHENTICATE_MESSAGE ;

/* Variables and functions */
 int CIFS_CPHTXT_SIZE ; 
 int /*<<< orphan*/  CIFS_MAX_DOMAINNAME_LEN ; 
 int /*<<< orphan*/  CIFS_MAX_USERNAME_LEN ; 
 int CIFS_SESS_KEY_SIZE ; 
 int strnlen (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int size_of_ntlmssp_blob(struct cifs_ses *ses)
{
	int sz = sizeof(AUTHENTICATE_MESSAGE) + ses->auth_key.len
		- CIFS_SESS_KEY_SIZE + CIFS_CPHTXT_SIZE + 2;

	if (ses->domainName)
		sz += 2 * strnlen(ses->domainName, CIFS_MAX_DOMAINNAME_LEN);
	else
		sz += 2;

	if (ses->user_name)
		sz += 2 * strnlen(ses->user_name, CIFS_MAX_USERNAME_LEN);
	else
		sz += 2;

	return sz;
}