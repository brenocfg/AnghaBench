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
struct nfs4_file {int /*<<< orphan*/  fi_lock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct file* find_writeable_file_locked (struct nfs4_file*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct file *
find_writeable_file(struct nfs4_file *f)
{
	struct file *ret;

	spin_lock(&f->fi_lock);
	ret = find_writeable_file_locked(f);
	spin_unlock(&f->fi_lock);

	return ret;
}