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
 int /*<<< orphan*/  NFS4ERR_MINOR_VERS_MISMATCH ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32
preprocess_nfs42_op(int nop, unsigned int op_nr, struct callback_op **op)
{
	return htonl(NFS4ERR_MINOR_VERS_MISMATCH);
}