#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  st_comp_ratio; int /*<<< orphan*/  st_alloc_efficiency; int /*<<< orphan*/  st_savings; int /*<<< orphan*/  st_usage; } ;
typedef  TYPE_1__ ZRAM_DEVICE ;
typedef  int /*<<< orphan*/  DICTIONARY ;

/* Variables and functions */
 int /*<<< orphan*/  dictionary_del (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dictionary_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  info (char*,char*) ; 
 int /*<<< orphan*/  rrdset_obsolete_and_pointer_null (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_device(DICTIONARY *dict, char *name)
{
    ZRAM_DEVICE *d = (ZRAM_DEVICE*)dictionary_get(dict, name);
    info("ZRAM : Disabling monitoring of device %s", name);
    rrdset_obsolete_and_pointer_null(d->st_usage);
    rrdset_obsolete_and_pointer_null(d->st_savings);
    rrdset_obsolete_and_pointer_null(d->st_alloc_efficiency);
    rrdset_obsolete_and_pointer_null(d->st_comp_ratio);
    dictionary_del(dict, name);
}