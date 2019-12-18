#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* distpoint; } ;
struct TYPE_5__ {int /*<<< orphan*/ * fullname; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ name; } ;
typedef  int /*<<< orphan*/  GENERAL_NAMES ;
typedef  int /*<<< orphan*/  GENERAL_NAME ;
typedef  TYPE_3__ DIST_POINT ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 scalar_t__ ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GENERAL_NAME_get0_value (int /*<<< orphan*/ *,int*) ; 
 int GEN_URI ; 
 int sk_GENERAL_NAME_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_GENERAL_NAME_value (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static const char *get_dp_url(DIST_POINT *dp)
{
    GENERAL_NAMES *gens;
    GENERAL_NAME *gen;
    int i, gtype;
    ASN1_STRING *uri;
    if (!dp->distpoint || dp->distpoint->type != 0)
        return NULL;
    gens = dp->distpoint->name.fullname;
    for (i = 0; i < sk_GENERAL_NAME_num(gens); i++) {
        gen = sk_GENERAL_NAME_value(gens, i);
        uri = GENERAL_NAME_get0_value(gen, &gtype);
        if (gtype == GEN_URI && ASN1_STRING_length(uri) > 6) {
            const char *uptr = (const char *)ASN1_STRING_get0_data(uri);
            if (strncmp(uptr, "http://", 7) == 0)
                return uptr;
        }
    }
    return NULL;
}