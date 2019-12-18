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
typedef  scalar_t__ u32 ;
struct sockaddr_vm {scalar_t__ svm_port; int /*<<< orphan*/  svm_cid; } ;
struct vsock_sock {struct sockaddr_vm local_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_BIND_SERVICE ; 
 int EACCES ; 
 int EADDRINUSE ; 
 int EADDRNOTAVAIL ; 
 scalar_t__ LAST_RESERVED_PORT ; 
 unsigned int MAX_PORT_RETRIES ; 
 scalar_t__ U32_MAX ; 
 scalar_t__ VMADDR_PORT_ANY ; 
 scalar_t__ __vsock_find_bound_socket (struct sockaddr_vm*) ; 
 int /*<<< orphan*/  __vsock_insert_bound (int /*<<< orphan*/ ,struct vsock_sock*) ; 
 int /*<<< orphan*/  __vsock_remove_bound (struct vsock_sock*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ prandom_u32_max (scalar_t__) ; 
 int /*<<< orphan*/  vsock_addr_init (struct sockaddr_vm*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vsock_bound_sockets (struct sockaddr_vm*) ; 

__attribute__((used)) static int __vsock_bind_stream(struct vsock_sock *vsk,
			       struct sockaddr_vm *addr)
{
	static u32 port;
	struct sockaddr_vm new_addr;

	if (!port)
		port = LAST_RESERVED_PORT + 1 +
			prandom_u32_max(U32_MAX - LAST_RESERVED_PORT);

	vsock_addr_init(&new_addr, addr->svm_cid, addr->svm_port);

	if (addr->svm_port == VMADDR_PORT_ANY) {
		bool found = false;
		unsigned int i;

		for (i = 0; i < MAX_PORT_RETRIES; i++) {
			if (port <= LAST_RESERVED_PORT)
				port = LAST_RESERVED_PORT + 1;

			new_addr.svm_port = port++;

			if (!__vsock_find_bound_socket(&new_addr)) {
				found = true;
				break;
			}
		}

		if (!found)
			return -EADDRNOTAVAIL;
	} else {
		/* If port is in reserved range, ensure caller
		 * has necessary privileges.
		 */
		if (addr->svm_port <= LAST_RESERVED_PORT &&
		    !capable(CAP_NET_BIND_SERVICE)) {
			return -EACCES;
		}

		if (__vsock_find_bound_socket(&new_addr))
			return -EADDRINUSE;
	}

	vsock_addr_init(&vsk->local_addr, new_addr.svm_cid, new_addr.svm_port);

	/* Remove stream sockets from the unbound list and add them to the hash
	 * table for easy lookup by its address.  The unbound list is simply an
	 * extra entry at the end of the hash table, a trick used by AF_UNIX.
	 */
	__vsock_remove_bound(vsk);
	__vsock_insert_bound(vsock_bound_sockets(&vsk->local_addr), vsk);

	return 0;
}