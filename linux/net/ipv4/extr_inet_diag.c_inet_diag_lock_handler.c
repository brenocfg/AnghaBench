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
struct inet_diag_handler {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  ENOENT ; 
 struct inet_diag_handler const* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct inet_diag_handler const** inet_diag_table ; 
 int /*<<< orphan*/  inet_diag_table_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_load_diag_module (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static const struct inet_diag_handler *inet_diag_lock_handler(int proto)
{
	if (!inet_diag_table[proto])
		sock_load_diag_module(AF_INET, proto);

	mutex_lock(&inet_diag_table_mutex);
	if (!inet_diag_table[proto])
		return ERR_PTR(-ENOENT);

	return inet_diag_table[proto];
}