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
struct tcp_md5sig {int tcpm_keylen; int /*<<< orphan*/  tcpm_key; int /*<<< orphan*/  tcpm_addr; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  md5sig ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  TCP_MD5SIG ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  log_err_errno (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (struct tcp_md5sig*,int /*<<< orphan*/ ,int) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tcp_md5sig*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int tcp_md5sig(int sd, void *addr, socklen_t alen, const char *password)
{
	struct tcp_md5sig md5sig;
	int keylen = password ? strlen(password) : 0;
	int rc;

	memset(&md5sig, 0, sizeof(md5sig));
	memcpy(&md5sig.tcpm_addr, addr, alen);
	md5sig.tcpm_keylen = keylen;

	if (keylen)
		memcpy(md5sig.tcpm_key, password, keylen);

	rc = setsockopt(sd, IPPROTO_TCP, TCP_MD5SIG, &md5sig, sizeof(md5sig));
	if (rc < 0) {
		/* ENOENT is harmless. Returned when a password is cleared */
		if (errno == ENOENT)
			rc = 0;
		else
			log_err_errno("setsockopt(TCP_MD5SIG)");
	}

	return rc;
}