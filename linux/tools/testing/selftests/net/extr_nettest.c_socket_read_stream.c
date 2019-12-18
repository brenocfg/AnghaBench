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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  interactive ; 
 int /*<<< orphan*/  log_err_errno (char*) ; 
 int /*<<< orphan*/  log_msg (char*,...) ; 
 int read (int,char*,int) ; 
 scalar_t__ server_mode ; 
 scalar_t__ write (int,char*,int) ; 

__attribute__((used)) static int socket_read_stream(int sd)
{
	char buf[1024];
	int len;

	len = read(sd, buf, sizeof(buf)-1);
	if (len == 0) {
		log_msg("client closed connection.\n");
		return 0;
	} else if (len < 0) {
		log_msg("failed to read message\n");
		return -1;
	}

	buf[len] = '\0';
	log_msg("Incoming message:\n");
	log_msg("    %.24s%s\n", buf, len > 24 ? " ..." : "");

	if (!interactive && server_mode) {
		if (write(sd, buf, len) < 0) {
			log_err_errno("failed to send buf");
			return -1;
		}
		log_msg("Sent message:\n");
		log_msg("     %.24s%s\n", buf, len > 24 ? " ..." : "");
	}

	return 1;
}