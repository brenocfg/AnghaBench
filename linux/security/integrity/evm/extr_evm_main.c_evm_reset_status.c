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
struct integrity_iint_cache {int /*<<< orphan*/  evm_status; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEGRITY_UNKNOWN ; 
 struct integrity_iint_cache* integrity_iint_find (struct inode*) ; 

__attribute__((used)) static void evm_reset_status(struct inode *inode)
{
	struct integrity_iint_cache *iint;

	iint = integrity_iint_find(inode);
	if (iint)
		iint->evm_status = INTEGRITY_UNKNOWN;
}