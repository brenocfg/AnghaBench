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
struct nfsd4_open {int op_deleg_want; int /*<<< orphan*/  op_why_no_deleg; int /*<<< orphan*/  op_delegate_type; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  NFS4_OPEN_DELEGATE_NONE_EXT ; 
#define  NFS4_SHARE_WANT_ANY_DELEG 132 
#define  NFS4_SHARE_WANT_CANCEL 131 
#define  NFS4_SHARE_WANT_NO_DELEG 130 
#define  NFS4_SHARE_WANT_READ_DELEG 129 
#define  NFS4_SHARE_WANT_WRITE_DELEG 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WND4_CANCELLED ; 
 int /*<<< orphan*/  WND4_CONTENTION ; 
 int /*<<< orphan*/  WND4_RESOURCE ; 

__attribute__((used)) static void nfsd4_open_deleg_none_ext(struct nfsd4_open *open, int status)
{
	open->op_delegate_type = NFS4_OPEN_DELEGATE_NONE_EXT;
	if (status == -EAGAIN)
		open->op_why_no_deleg = WND4_CONTENTION;
	else {
		open->op_why_no_deleg = WND4_RESOURCE;
		switch (open->op_deleg_want) {
		case NFS4_SHARE_WANT_READ_DELEG:
		case NFS4_SHARE_WANT_WRITE_DELEG:
		case NFS4_SHARE_WANT_ANY_DELEG:
			break;
		case NFS4_SHARE_WANT_CANCEL:
			open->op_why_no_deleg = WND4_CANCELLED;
			break;
		case NFS4_SHARE_WANT_NO_DELEG:
			WARN_ON_ONCE(1);
		}
	}
}