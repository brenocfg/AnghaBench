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
struct cifs_ses {int /*<<< orphan*/  server; } ;

/* Variables and functions */
 int CIFSSMBNegotiate (unsigned int const,struct cifs_ses*) ; 
 int EAGAIN ; 
 int EHOSTDOWN ; 
 int /*<<< orphan*/  set_credits (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
cifs_negotiate(const unsigned int xid, struct cifs_ses *ses)
{
	int rc;
	rc = CIFSSMBNegotiate(xid, ses);
	if (rc == -EAGAIN) {
		/* retry only once on 1st time connection */
		set_credits(ses->server, 1);
		rc = CIFSSMBNegotiate(xid, ses);
		if (rc == -EAGAIN)
			rc = -EHOSTDOWN;
	}
	return rc;
}