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
typedef  int /*<<< orphan*/  RRDVAR ;

/* Variables and functions */
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  localhost ; 
 int /*<<< orphan*/  netdata_configured_host_prefix ; 
 scalar_t__ read_file (char*,char*,int) ; 
 int /*<<< orphan*/ * rrdvar_custom_host_variable_create (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rrdvar_custom_host_variable_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long long) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* strdupz (char*) ; 
 unsigned long long strtoull (char*,char**,int) ; 
 unsigned long long sysconf (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int read_tcp_mem(void) {
    static char *filename = NULL;
    static RRDVAR *tcp_mem_low_threshold = NULL,
                  *tcp_mem_pressure_threshold = NULL,
                  *tcp_mem_high_threshold = NULL;

    if(unlikely(!tcp_mem_low_threshold)) {
        tcp_mem_low_threshold      = rrdvar_custom_host_variable_create(localhost, "tcp_mem_low");
        tcp_mem_pressure_threshold = rrdvar_custom_host_variable_create(localhost, "tcp_mem_pressure");
        tcp_mem_high_threshold     = rrdvar_custom_host_variable_create(localhost, "tcp_mem_high");
    }

    if(unlikely(!filename)) {
        char buffer[FILENAME_MAX + 1];
        snprintfz(buffer, FILENAME_MAX, "%s/proc/sys/net/ipv4/tcp_mem", netdata_configured_host_prefix);
        filename = strdupz(buffer);
    }

    char buffer[200 + 1], *start, *end;
    if(read_file(filename, buffer, 200) != 0) return 1;
    buffer[200] = '\0';

    unsigned long long low = 0, pressure = 0, high = 0;

    start = buffer;
    low = strtoull(start, &end, 10);

    start = end;
    pressure = strtoull(start, &end, 10);

    start = end;
    high = strtoull(start, &end, 10);

    // fprintf(stderr, "TCP MEM low = %llu, pressure = %llu, high = %llu\n", low, pressure, high);

    rrdvar_custom_host_variable_set(localhost, tcp_mem_low_threshold, low * sysconf(_SC_PAGESIZE) / 1024.0);
    rrdvar_custom_host_variable_set(localhost, tcp_mem_pressure_threshold, pressure * sysconf(_SC_PAGESIZE) / 1024.0);
    rrdvar_custom_host_variable_set(localhost, tcp_mem_high_threshold, high * sysconf(_SC_PAGESIZE) / 1024.0);

    return 0;
}