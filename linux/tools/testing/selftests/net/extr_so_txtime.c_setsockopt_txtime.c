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
struct sock_txtime {int /*<<< orphan*/  member_0; int /*<<< orphan*/  clockid; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  so_txtime_val ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_TXTIME ; 
 int /*<<< orphan*/  cfg_clockid ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sock_txtime*,int*) ; 
 scalar_t__ memcmp (struct sock_txtime*,struct sock_txtime*,int) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sock_txtime*,int) ; 

__attribute__((used)) static void setsockopt_txtime(int fd)
{
	struct sock_txtime so_txtime_val = { .clockid = cfg_clockid };
	struct sock_txtime so_txtime_val_read = { 0 };
	socklen_t vallen = sizeof(so_txtime_val);

	if (setsockopt(fd, SOL_SOCKET, SO_TXTIME,
		       &so_txtime_val, sizeof(so_txtime_val)))
		error(1, errno, "setsockopt txtime");

	if (getsockopt(fd, SOL_SOCKET, SO_TXTIME,
		       &so_txtime_val_read, &vallen))
		error(1, errno, "getsockopt txtime");

	if (vallen != sizeof(so_txtime_val) ||
	    memcmp(&so_txtime_val, &so_txtime_val_read, vallen))
		error(1, 0, "getsockopt txtime: mismatch");
}