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

/* Variables and functions */
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int read_single_number_file (char*,unsigned long long*) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,char const*,char const*) ; 

unsigned int read_iface_iflink(const char *prefix, const char *iface) {
    if(!prefix) prefix = "";

    char filename[FILENAME_MAX + 1];
    snprintfz(filename, FILENAME_MAX, "%s/sys/class/net/%s/iflink", prefix, iface);

    unsigned long long iflink = 0;
    int ret = read_single_number_file(filename, &iflink);
    if(ret) error("Cannot read '%s'.", filename);

    return (unsigned int)iflink;
}