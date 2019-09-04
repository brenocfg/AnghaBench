#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tm {int tm_wday; int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;
struct interface_info {char* name; } ;
struct client_lease {char* filename; char* server_name; int /*<<< orphan*/  expiry; int /*<<< orphan*/  rebind; int /*<<< orphan*/  renewal; TYPE_2__* options; TYPE_1__* medium; int /*<<< orphan*/  address; scalar_t__ is_bootp; scalar_t__ is_static; } ;
struct TYPE_6__ {char* name; } ;
struct TYPE_5__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {char* string; } ;

/* Variables and functions */
 TYPE_3__* dhcp_options ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 scalar_t__ fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 struct tm* gmtime (int /*<<< orphan*/ *) ; 
 scalar_t__ leaseFile ; 
 int /*<<< orphan*/  path_dhclient_db ; 
 char* piaddr (int /*<<< orphan*/ ) ; 
 char* pretty_print_option (int,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  rewrite_client_leases (struct interface_info*) ; 

void
write_client_lease(struct interface_info *ip, struct client_lease *lease,
    int rewrite)
{
	static int leases_written;
	struct tm *t;
	int i;

	if (!rewrite) {
		if (leases_written++ > 20) {
			rewrite_client_leases(ip);
			leases_written = 0;
		}
	}

	/* If the lease came from the config file, we don't need to stash
	   a copy in the lease database. */
	if (lease->is_static)
		return;

	if (!leaseFile) {	/* XXX */
		leaseFile = fopen(path_dhclient_db, "w");
		if (!leaseFile) {
			error("can't create %s", path_dhclient_db);
                        return;
                }
	}

	fprintf(leaseFile, "lease {\n");
	if (lease->is_bootp)
		fprintf(leaseFile, "  bootp;\n");
	fprintf(leaseFile, "  interface \"%s\";\n", ip->name);
	fprintf(leaseFile, "  fixed-address %s;\n", piaddr(lease->address));
	if (lease->filename)
		fprintf(leaseFile, "  filename \"%s\";\n", lease->filename);
	if (lease->server_name)
		fprintf(leaseFile, "  server-name \"%s\";\n",
		    lease->server_name);
	if (lease->medium)
		fprintf(leaseFile, "  medium \"%s\";\n", lease->medium->string);
	for (i = 0; i < 256; i++)
		if (lease->options[i].len)
			fprintf(leaseFile, "  option %s %s;\n",
			    dhcp_options[i].name,
			    pretty_print_option(i, lease->options[i].data,
			    lease->options[i].len, 1, 1));

	t = gmtime(&lease->renewal);
        if (t)
	    fprintf(leaseFile, "  renew %d %d/%d/%d %02d:%02d:%02d;\n",
	        t->tm_wday, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
	        t->tm_hour, t->tm_min, t->tm_sec);
	t = gmtime(&lease->rebind);
        if (t)
	    fprintf(leaseFile, "  rebind %d %d/%d/%d %02d:%02d:%02d;\n",
	         t->tm_wday, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
	         t->tm_hour, t->tm_min, t->tm_sec);
	t = gmtime(&lease->expiry);
        if (t)
	    fprintf(leaseFile, "  expire %d %d/%d/%d %02d:%02d:%02d;\n",
	        t->tm_wday, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
	        t->tm_hour, t->tm_min, t->tm_sec);
	fprintf(leaseFile, "}\n");
	fflush(leaseFile);
}