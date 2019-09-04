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
struct ocfs2_xattr_info {int /*<<< orphan*/  xi_value_len; int /*<<< orphan*/  xi_name_len; } ;

/* Variables and functions */
 int namevalue_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int namevalue_size_xi(struct ocfs2_xattr_info *xi)
{
	return namevalue_size(xi->xi_name_len, xi->xi_value_len);
}