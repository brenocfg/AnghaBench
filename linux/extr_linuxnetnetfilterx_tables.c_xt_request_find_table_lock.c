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
typedef  int /*<<< orphan*/  u_int8_t ;
struct xt_table {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct xt_table* xt_find_table_lock (struct net*,int /*<<< orphan*/ ,char const*) ; 

struct xt_table *xt_request_find_table_lock(struct net *net, u_int8_t af,
					    const char *name)
{
	struct xt_table *t = xt_find_table_lock(net, af, name);

#ifdef CONFIG_MODULES
	if (IS_ERR(t)) {
		int err = request_module("%stable_%s", xt_prefix[af], name);
		if (err < 0)
			return ERR_PTR(err);
		t = xt_find_table_lock(net, af, name);
	}
#endif

	return t;
}