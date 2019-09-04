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
struct socket {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_PASSCRED ; 
 int /*<<< orphan*/  SOCK_PASSSEC ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unix_sock_inherit_flags(const struct socket *old,
				    struct socket *new)
{
	if (test_bit(SOCK_PASSCRED, &old->flags))
		set_bit(SOCK_PASSCRED, &new->flags);
	if (test_bit(SOCK_PASSSEC, &old->flags))
		set_bit(SOCK_PASSSEC, &new->flags);
}