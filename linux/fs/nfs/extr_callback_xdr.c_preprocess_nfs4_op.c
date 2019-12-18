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
struct callback_op {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4ERR_OP_ILLEGAL ; 
 int /*<<< orphan*/  NFS_OK ; 
#define  OP_CB_GETATTR 129 
#define  OP_CB_RECALL 128 
 struct callback_op* callback_ops ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32
preprocess_nfs4_op(unsigned int op_nr, struct callback_op **op)
{
	switch (op_nr) {
	case OP_CB_GETATTR:
	case OP_CB_RECALL:
		*op = &callback_ops[op_nr];
		break;
	default:
		return htonl(NFS4ERR_OP_ILLEGAL);
	}

	return htonl(NFS_OK);
}