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
struct ubifs_znode {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  COW_ZNODE ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ubifs_zn_cow(const struct ubifs_znode *znode)
{
	return !!test_bit(COW_ZNODE, &znode->flags);
}