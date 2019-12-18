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
struct hwdec_info {char* method_name; int rank; int auto_pos; TYPE_1__* codec; int /*<<< orphan*/  name; scalar_t__ copying; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (int /*<<< orphan*/ *,struct hwdec_info*,int,struct hwdec_info) ; 
 scalar_t__* hwdec_autoprobe_order ; 
 int /*<<< orphan*/  mp_snprintf_cat (char*,int,char*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

__attribute__((used)) static void add_hwdec_item(struct hwdec_info **infos, int *num_infos,
                           struct hwdec_info info)
{
    if (info.copying)
        mp_snprintf_cat(info.method_name, sizeof(info.method_name), "-copy");

    // (Including the codec name in case this is a wrapper looks pretty dumb,
    // but better not have them clash with hwaccels and others.)
    snprintf(info.name, sizeof(info.name), "%s-%s",
             info.codec->name, info.method_name);

    info.rank = *num_infos;
    info.auto_pos = INT_MAX;
    for (int x = 0; hwdec_autoprobe_order[x]; x++) {
        if (strcmp(hwdec_autoprobe_order[x], info.method_name) == 0)
            info.auto_pos = x;
    }

    MP_TARRAY_APPEND(NULL, *infos, *num_infos, info);
}