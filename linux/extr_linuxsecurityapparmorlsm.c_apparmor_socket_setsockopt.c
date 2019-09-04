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
struct socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_MAY_SETOPT ; 
 int /*<<< orphan*/  OP_SETSOCKOPT ; 
 int aa_sock_opt_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket*,int,int) ; 

__attribute__((used)) static int apparmor_socket_setsockopt(struct socket *sock, int level,
				      int optname)
{
	return aa_sock_opt_perm(OP_SETSOCKOPT, AA_MAY_SETOPT, sock,
				level, optname);
}