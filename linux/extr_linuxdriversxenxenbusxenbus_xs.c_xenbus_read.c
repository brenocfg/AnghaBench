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
struct xenbus_transaction {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (char*) ; 
 int /*<<< orphan*/  XS_READ ; 
 char* join (char const*,char const*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 void* xs_single (struct xenbus_transaction,int /*<<< orphan*/ ,char*,unsigned int*) ; 

void *xenbus_read(struct xenbus_transaction t,
		  const char *dir, const char *node, unsigned int *len)
{
	char *path;
	void *ret;

	path = join(dir, node);
	if (IS_ERR(path))
		return (void *)path;

	ret = xs_single(t, XS_READ, path, len);
	kfree(path);
	return ret;
}