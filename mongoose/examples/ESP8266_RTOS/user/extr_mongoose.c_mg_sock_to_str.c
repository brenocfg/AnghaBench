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
typedef  union socket_address {int dummy; } socket_address ;
typedef  int /*<<< orphan*/  sock_t ;

/* Variables and functions */
 int MG_SOCK_STRINGIFY_REMOTE ; 
 int /*<<< orphan*/  mg_sock_addr_to_str (union socket_address*,char*,size_t,int) ; 
 int /*<<< orphan*/  mg_sock_get_addr (int /*<<< orphan*/ ,int,union socket_address*) ; 

void mg_sock_to_str(sock_t sock, char *buf, size_t len, int flags) {
  union socket_address sa;
  mg_sock_get_addr(sock, flags & MG_SOCK_STRINGIFY_REMOTE, &sa);
  mg_sock_addr_to_str(&sa, buf, len, flags);
}