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
struct fasync_struct {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct fasync_struct* fasync_alloc () ; 
 int /*<<< orphan*/  fasync_free (struct fasync_struct*) ; 
 scalar_t__ fasync_insert_entry (int,struct file*,struct fasync_struct**,struct fasync_struct*) ; 

__attribute__((used)) static int fasync_add_entry(int fd, struct file *filp, struct fasync_struct **fapp)
{
	struct fasync_struct *new;

	new = fasync_alloc();
	if (!new)
		return -ENOMEM;

	/*
	 * fasync_insert_entry() returns the old (update) entry if
	 * it existed.
	 *
	 * So free the (unused) new entry and return 0 to let the
	 * caller know that we didn't add any new fasync entries.
	 */
	if (fasync_insert_entry(fd, filp, fapp, new)) {
		fasync_free(new);
		return 0;
	}

	return 1;
}