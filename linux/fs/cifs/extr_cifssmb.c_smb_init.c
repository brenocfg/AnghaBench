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
struct cifs_tcon {int dummy; } ;

/* Variables and functions */
 int __smb_init (int,int,struct cifs_tcon*,void**,void**) ; 
 int cifs_reconnect_tcon (struct cifs_tcon*,int) ; 

__attribute__((used)) static int
smb_init(int smb_command, int wct, struct cifs_tcon *tcon,
	 void **request_buf, void **response_buf)
{
	int rc;

	rc = cifs_reconnect_tcon(tcon, smb_command);
	if (rc)
		return rc;

	return __smb_init(smb_command, wct, tcon, request_buf, response_buf);
}