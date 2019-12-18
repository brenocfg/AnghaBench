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
struct perm_datum {int value; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_permissions_callback(void *k, void *d, void *args)
{
	struct perm_datum *datum = d;
	char *name = k, **perms = args;
	int value = datum->value - 1;

	perms[value] = kstrdup(name, GFP_ATOMIC);
	if (!perms[value])
		return -ENOMEM;

	return 0;
}