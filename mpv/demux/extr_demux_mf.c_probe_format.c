#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * names; } ;
typedef  TYPE_1__ mf_t ;
typedef  enum demux_check { ____Placeholder_demux_check } demux_check ;
struct TYPE_6__ {char const* codec; scalar_t__ type; } ;

/* Variables and functions */
 int DEMUX_CHECK_REQUEST ; 
 int /*<<< orphan*/  MP_ERR (TYPE_1__*,char*) ; 
 scalar_t__ strcasecmp (char*,scalar_t__) ; 
 char* strrchr (int /*<<< orphan*/ ,char) ; 
 TYPE_2__* type2format ; 

__attribute__((used)) static const char *probe_format(mf_t *mf, char *type, enum demux_check check)
{
    if (check > DEMUX_CHECK_REQUEST)
        return NULL;
    char *org_type = type;
    if (!type || !type[0]) {
        char *p = strrchr(mf->names[0], '.');
        if (p)
            type = p + 1;
    }
    for (int i = 0; type2format[i].type; i++) {
        if (type && strcasecmp(type, type2format[i].type) == 0)
            return type2format[i].codec;
    }
    if (check == DEMUX_CHECK_REQUEST) {
        if (!org_type) {
            MP_ERR(mf, "file type was not set! (try --mf-type=ext)\n");
        } else {
            MP_ERR(mf, "--mf-type set to an unknown codec!\n");
        }
    }
    return NULL;
}