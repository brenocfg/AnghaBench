#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int first_t; int last_t; int usages; int flags; TYPE_1__* url; } ;
struct TYPE_3__ {char* url; } ;
typedef  TYPE_2__ REGISTRY_MACHINE_URL ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  D_REGISTRY ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char*) ; 
 int fprintf (int /*<<< orphan*/ *,char*,int,int,int,int,char*) ; 

__attribute__((used)) static int registry_machine_save_url(void *entry, void *file) {
    REGISTRY_MACHINE_URL *mu = entry;
    FILE *fp = file;

    debug(D_REGISTRY, "Registry: registry_machine_save_url('%s')", mu->url->url);

    int ret = fprintf(fp, "V\t%08x\t%08x\t%08x\t%02x\t%s\n",
            mu->first_t,
            mu->last_t,
            mu->usages,
            mu->flags,
            mu->url->url
    );

    // error handling is done at registry_db_save()

    return ret;
}