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
struct address_space {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_EIO ; 
 int /*<<< orphan*/  AS_ENOSPC ; 
 int EIO ; 
 int ENOSPC ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int filemap_check_and_keep_errors(struct address_space *mapping)
{
	/* Check for outstanding write errors */
	if (test_bit(AS_EIO, &mapping->flags))
		return -EIO;
	if (test_bit(AS_ENOSPC, &mapping->flags))
		return -ENOSPC;
	return 0;
}