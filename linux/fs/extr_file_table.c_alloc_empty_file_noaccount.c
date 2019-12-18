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
struct file {int /*<<< orphan*/  f_mode; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_NOACCOUNT ; 
 int /*<<< orphan*/  IS_ERR (struct file*) ; 
 struct file* __alloc_file (int,struct cred const*) ; 

struct file *alloc_empty_file_noaccount(int flags, const struct cred *cred)
{
	struct file *f = __alloc_file(flags, cred);

	if (!IS_ERR(f))
		f->f_mode |= FMODE_NOACCOUNT;

	return f;
}