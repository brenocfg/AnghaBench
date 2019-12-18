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
struct sockaddr {int dummy; } ;
struct smbd_connection {int dummy; } ;
struct TCP_Server_Info {int dummy; } ;

/* Variables and functions */
 int SMBD_PORT ; 
 int SMB_PORT ; 
 struct smbd_connection* _smbd_get_connection (struct TCP_Server_Info*,struct sockaddr*,int) ; 

struct smbd_connection *smbd_get_connection(
	struct TCP_Server_Info *server, struct sockaddr *dstaddr)
{
	struct smbd_connection *ret;
	int port = SMBD_PORT;

try_again:
	ret = _smbd_get_connection(server, dstaddr, port);

	/* Try SMB_PORT if SMBD_PORT doesn't work */
	if (!ret && port == SMBD_PORT) {
		port = SMB_PORT;
		goto try_again;
	}
	return ret;
}