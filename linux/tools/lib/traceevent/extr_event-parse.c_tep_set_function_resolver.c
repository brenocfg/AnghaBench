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
typedef  int /*<<< orphan*/  tep_func_resolver_t ;
struct tep_handle {struct func_resolver* func_resolver; } ;
struct func_resolver {void* priv; int /*<<< orphan*/ * func; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct func_resolver*) ; 
 struct func_resolver* malloc (int) ; 

int tep_set_function_resolver(struct tep_handle *tep,
			      tep_func_resolver_t *func, void *priv)
{
	struct func_resolver *resolver = malloc(sizeof(*resolver));

	if (resolver == NULL)
		return -1;

	resolver->func = func;
	resolver->priv = priv;

	free(tep->func_resolver);
	tep->func_resolver = resolver;

	return 0;
}