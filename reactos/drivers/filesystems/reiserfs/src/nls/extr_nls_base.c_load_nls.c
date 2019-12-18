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
struct nls_table {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 struct nls_table* find_nls (char*) ; 
 int /*<<< orphan*/  printk (char*,char*) ; 
 int request_module (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int strlen (char*) ; 

struct nls_table *load_nls(char *charset)
{
	struct nls_table *nls;
#ifdef CONFIG_KMOD
	char buf[40];
	int ret;
#endif

	nls = find_nls(charset);
	if (nls)
		return nls;

#ifdef CONFIG_KMOD
	if (strlen(charset) > sizeof(buf) - sizeof("nls_")) {
		printk("Unable to load NLS charset %s: name too long\n",
			charset);
		return NULL;
	}
		
	sprintf(buf, "nls_%s", charset);
	ret = request_module(buf);
	if (ret != 0) {
		printk("Unable to load NLS charset %s\n", charset);
		return NULL;
	}
	nls = find_nls(charset);
#endif
	return nls;
}