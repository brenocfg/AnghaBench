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
typedef  unsigned long long kernel_uint_t ;
typedef  int /*<<< orphan*/  RRDVAR ;

/* Variables and functions */
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  localhost ; 
 int /*<<< orphan*/  netdata_configured_host_prefix ; 
 scalar_t__ read_single_number_file (char*,unsigned long long*) ; 
 int /*<<< orphan*/ * rrdvar_custom_host_variable_create (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rrdvar_custom_host_variable_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long long) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* strdupz (char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static kernel_uint_t read_tcp_max_orphans(void) {
    static char *filename = NULL;
    static RRDVAR *tcp_max_orphans_var = NULL;

    if(unlikely(!filename)) {
        char buffer[FILENAME_MAX + 1];
        snprintfz(buffer, FILENAME_MAX, "%s/proc/sys/net/ipv4/tcp_max_orphans", netdata_configured_host_prefix);
        filename = strdupz(buffer);
    }

    unsigned long long tcp_max_orphans = 0;
    if(read_single_number_file(filename, &tcp_max_orphans) == 0) {

        if(unlikely(!tcp_max_orphans_var))
            tcp_max_orphans_var = rrdvar_custom_host_variable_create(localhost, "tcp_max_orphans");

        rrdvar_custom_host_variable_set(localhost, tcp_max_orphans_var, tcp_max_orphans);
        return  tcp_max_orphans;
    }

    return 0;
}