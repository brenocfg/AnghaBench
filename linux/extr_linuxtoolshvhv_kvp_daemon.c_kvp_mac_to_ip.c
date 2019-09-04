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
struct hv_kvp_ipaddr_value {scalar_t__ ip_addr; scalar_t__ adapter_id; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  dev_id ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int HV_E_FAIL ; 
 char* KVP_NET_DIR ; 
 int /*<<< orphan*/  KVP_OP_GET_IP_INFO ; 
 int MAX_IP_ADDR_SIZE ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int kvp_get_ip_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct hv_kvp_ipaddr_value*,int) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 unsigned int strlen (char*) ; 
 char toupper (char) ; 

__attribute__((used)) static int kvp_mac_to_ip(struct hv_kvp_ipaddr_value *kvp_ip_val)
{
	char *mac = (char *)kvp_ip_val->adapter_id;
	DIR *dir;
	struct dirent *entry;
	FILE    *file;
	char    *p, *x;
	char    *if_name = NULL;
	char    buf[256];
	char dev_id[PATH_MAX];
	unsigned int i;
	int error = HV_E_FAIL;

	dir = opendir(KVP_NET_DIR);
	if (dir == NULL)
		return HV_E_FAIL;

	while ((entry = readdir(dir)) != NULL) {
		/*
		 * Set the state for the next pass.
		 */
		snprintf(dev_id, sizeof(dev_id), "%s%s/address", KVP_NET_DIR,
			 entry->d_name);

		file = fopen(dev_id, "r");
		if (file == NULL)
			continue;

		p = fgets(buf, sizeof(buf), file);
		fclose(file);
		if (!p)
			continue;

		x = strchr(p, '\n');
		if (x)
			*x = '\0';

		for (i = 0; i < strlen(p); i++)
			p[i] = toupper(p[i]);

		if (strcmp(p, mac))
			continue;

		/*
		 * Found the MAC match.
		 * A NIC (e.g. VF) matching the MAC, but without IP, is skipped.
		 */
		if_name = entry->d_name;
		if (!if_name)
			continue;

		error = kvp_get_ip_info(0, if_name, KVP_OP_GET_IP_INFO,
					kvp_ip_val, MAX_IP_ADDR_SIZE * 2);

		if (!error && strlen((char *)kvp_ip_val->ip_addr))
			break;
	}

	closedir(dir);
	return error;
}