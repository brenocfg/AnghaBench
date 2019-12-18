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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct vmci_qp {int dummy; } ;
struct vmci_handle {int dummy; } ;

/* Variables and functions */
 int VMCI_ERROR_NO_ACCESS ; 
 int /*<<< orphan*/  VMCI_NO_PRIVILEGE_FLAGS ; 
 int /*<<< orphan*/  VMCI_PRIVILEGE_FLAG_TRUSTED ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int vmci_qpair_alloc (struct vmci_qp**,struct vmci_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vmci_transport_error_to_vsock_error (int) ; 

__attribute__((used)) static int
vmci_transport_queue_pair_alloc(struct vmci_qp **qpair,
				struct vmci_handle *handle,
				u64 produce_size,
				u64 consume_size,
				u32 peer, u32 flags, bool trusted)
{
	int err = 0;

	if (trusted) {
		/* Try to allocate our queue pair as trusted. This will only
		 * work if vsock is running in the host.
		 */

		err = vmci_qpair_alloc(qpair, handle, produce_size,
				       consume_size,
				       peer, flags,
				       VMCI_PRIVILEGE_FLAG_TRUSTED);
		if (err != VMCI_ERROR_NO_ACCESS)
			goto out;

	}

	err = vmci_qpair_alloc(qpair, handle, produce_size, consume_size,
			       peer, flags, VMCI_NO_PRIVILEGE_FLAGS);
out:
	if (err < 0) {
		pr_err("Could not attach to queue pair with %d\n",
		       err);
		err = vmci_transport_error_to_vsock_error(err);
	}

	return err;
}