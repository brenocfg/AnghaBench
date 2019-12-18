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
struct file {int dummy; } ;
struct dir_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int proc_pident_readdir (struct file*,struct dir_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgid_base_stuff ; 

__attribute__((used)) static int proc_tgid_base_readdir(struct file *file, struct dir_context *ctx)
{
	return proc_pident_readdir(file, ctx,
				   tgid_base_stuff, ARRAY_SIZE(tgid_base_stuff));
}