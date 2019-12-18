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
struct integrity_iint_cache {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_IMA (struct inode*) ; 
 struct integrity_iint_cache* __integrity_iint_find (struct inode*) ; 
 int /*<<< orphan*/  integrity_iint_lock ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

struct integrity_iint_cache *integrity_iint_find(struct inode *inode)
{
	struct integrity_iint_cache *iint;

	if (!IS_IMA(inode))
		return NULL;

	read_lock(&integrity_iint_lock);
	iint = __integrity_iint_find(inode);
	read_unlock(&integrity_iint_lock);

	return iint;
}