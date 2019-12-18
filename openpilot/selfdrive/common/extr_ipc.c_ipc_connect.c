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
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  SOCK_SEQPACKET ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ipc_connect(const char* socket_path) {
  int err;

  int sock = socket(AF_UNIX, SOCK_SEQPACKET, 0);
  assert(sock >= 0);
  struct sockaddr_un addr = {
    .sun_family = AF_UNIX,
  };
  snprintf(addr.sun_path, sizeof(addr.sun_path), "%s", socket_path);
  err = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  if (err != 0) {
    close(sock);
    return -1;
  }

  return sock;
}