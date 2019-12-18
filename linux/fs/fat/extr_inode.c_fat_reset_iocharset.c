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
struct fat_mount_options {scalar_t__ iocharset; } ;

/* Variables and functions */
 scalar_t__ fat_default_iocharset ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 

__attribute__((used)) static void fat_reset_iocharset(struct fat_mount_options *opts)
{
	if (opts->iocharset != fat_default_iocharset) {
		/* Note: opts->iocharset can be NULL here */
		kfree(opts->iocharset);
		opts->iocharset = fat_default_iocharset;
	}
}