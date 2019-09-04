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
typedef  int /*<<< orphan*/  umode_t ;
struct open_flags {int dummy; } ;
struct filename {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 struct file* ERR_PTR (int) ; 
 int build_open_flags (int,int /*<<< orphan*/ ,struct open_flags*) ; 
 struct file* do_filp_open (int /*<<< orphan*/ ,struct filename*,struct open_flags*) ; 

struct file *file_open_name(struct filename *name, int flags, umode_t mode)
{
	struct open_flags op;
	int err = build_open_flags(flags, mode, &op);
	return err ? ERR_PTR(err) : do_filp_open(AT_FDCWD, name, &op);
}