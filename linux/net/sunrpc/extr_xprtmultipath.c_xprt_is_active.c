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
struct rpc_xprt {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 scalar_t__ kref_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
bool xprt_is_active(const struct rpc_xprt *xprt)
{
	return kref_read(&xprt->kref) != 0;
}