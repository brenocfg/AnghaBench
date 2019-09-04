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
 int /*<<< orphan*/  dir_emit_dots (struct file*,struct dir_context*) ; 

__attribute__((used)) static int empty_dir_readdir(struct file *file, struct dir_context *ctx)
{
	dir_emit_dots(file, ctx);
	return 0;
}