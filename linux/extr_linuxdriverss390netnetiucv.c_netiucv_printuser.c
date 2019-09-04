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
struct iucv_connection {char* userdata; char* userid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBCASC (char*,int) ; 
 int /*<<< orphan*/  iucvMagic_ebcdic ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* netiucv_printname (char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 

__attribute__((used)) static char *netiucv_printuser(struct iucv_connection *conn)
{
	static char tmp_uid[9];
	static char tmp_udat[17];
	static char buf[100];

	if (memcmp(conn->userdata, iucvMagic_ebcdic, 16)) {
		tmp_uid[8] = '\0';
		tmp_udat[16] = '\0';
		memcpy(tmp_uid, netiucv_printname(conn->userid, 8), 8);
		memcpy(tmp_udat, conn->userdata, 16);
		EBCASC(tmp_udat, 16);
		memcpy(tmp_udat, netiucv_printname(tmp_udat, 16), 16);
		sprintf(buf, "%s.%s", tmp_uid, tmp_udat);
		return buf;
	} else
		return netiucv_printname(conn->userid, 8);
}