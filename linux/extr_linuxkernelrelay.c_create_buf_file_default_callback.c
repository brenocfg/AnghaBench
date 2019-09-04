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
struct rchan_buf {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct dentry *create_buf_file_default_callback(const char *filename,
						       struct dentry *parent,
						       umode_t mode,
						       struct rchan_buf *buf,
						       int *is_global)
{
	return NULL;
}