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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  addr_file ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* KVP_NET_DIR ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 unsigned int strlen (char*) ; 
 char toupper (char) ; 

__attribute__((used)) static char *kvp_if_name_to_mac(char *if_name)
{
	FILE    *file;
	char    *p, *x;
	char    buf[256];
	char addr_file[PATH_MAX];
	unsigned int i;
	char *mac_addr = NULL;

	snprintf(addr_file, sizeof(addr_file), "%s%s%s", KVP_NET_DIR,
		 if_name, "/address");

	file = fopen(addr_file, "r");
	if (file == NULL)
		return NULL;

	p = fgets(buf, sizeof(buf), file);
	if (p) {
		x = strchr(p, '\n');
		if (x)
			*x = '\0';
		for (i = 0; i < strlen(p); i++)
			p[i] = toupper(p[i]);
		mac_addr = strdup(p);
	}

	fclose(file);
	return mac_addr;
}