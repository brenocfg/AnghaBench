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
struct sock_args {int dummy; } ;

/* Variables and functions */
 int msock_init (struct sock_args*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msock_client(struct sock_args *args)
{
	return msock_init(args, 0);
}