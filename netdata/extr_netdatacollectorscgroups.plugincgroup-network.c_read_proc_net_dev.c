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
struct iface {struct iface* next; int /*<<< orphan*/  device; int /*<<< orphan*/  iflink; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  hash; } ;
typedef  int /*<<< orphan*/  procfile ;

/* Variables and functions */
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  PROCFILE_FLAG_DEFAULT ; 
 struct iface* callocz (int,int) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  procfile_close (int /*<<< orphan*/ *) ; 
 size_t procfile_lines (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  procfile_lineword (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int procfile_linewords (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * procfile_open (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * procfile_readall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_iface_ifindex (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_iface_iflink (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  strdupz (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct iface *read_proc_net_dev(const char *scope, const char *prefix) {
    if(!prefix) prefix = "";

    procfile *ff = NULL;
    char filename[FILENAME_MAX + 1];

    snprintfz(filename, FILENAME_MAX, "%s%s", prefix, (*prefix)?"/proc/1/net/dev":"/proc/net/dev");

#ifdef NETDATA_INTERNAL_CHECKS
    info("parsing '%s'", filename);
#endif

    ff = procfile_open(filename, " \t,:|", PROCFILE_FLAG_DEFAULT);
    if(unlikely(!ff)) {
        error("Cannot open file '%s'", filename);
        return NULL;
    }

    ff = procfile_readall(ff);
    if(unlikely(!ff)) {
        error("Cannot read file '%s'", filename);
        return NULL;
    }

    size_t lines = procfile_lines(ff), l;
    struct iface *root = NULL;
    for(l = 2; l < lines ;l++) {
        if (unlikely(procfile_linewords(ff, l) < 1)) continue;

        struct iface *t = callocz(1, sizeof(struct iface));
        t->device = strdupz(procfile_lineword(ff, l, 0));
        t->hash = simple_hash(t->device);
        t->ifindex = read_iface_ifindex(prefix, t->device);
        t->iflink  = read_iface_iflink(prefix, t->device);
        t->next = root;
        root = t;

#ifdef NETDATA_INTERNAL_CHECKS
        info("added %s interface '%s', ifindex %u, iflink %u", scope, t->device, t->ifindex, t->iflink);
#endif
    }

    procfile_close(ff);

    return root;
}