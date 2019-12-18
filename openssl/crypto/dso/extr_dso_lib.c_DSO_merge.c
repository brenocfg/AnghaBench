#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; char* (* merger ) (TYPE_2__*,char const*,char const*) ;TYPE_1__* meth; } ;
struct TYPE_6__ {char* (* dso_merger ) (TYPE_2__*,char const*,char const*) ;} ;
typedef  TYPE_2__ DSO ;

/* Variables and functions */
 int DSO_FLAG_NO_NAME_TRANSLATION ; 
 int /*<<< orphan*/  DSO_F_DSO_MERGE ; 
 int /*<<< orphan*/  DSOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 char* stub1 (TYPE_2__*,char const*,char const*) ; 
 char* stub2 (TYPE_2__*,char const*,char const*) ; 

char *DSO_merge(DSO *dso, const char *filespec1, const char *filespec2)
{
    char *result = NULL;

    if (dso == NULL || filespec1 == NULL) {
        DSOerr(DSO_F_DSO_MERGE, ERR_R_PASSED_NULL_PARAMETER);
        return NULL;
    }
    if ((dso->flags & DSO_FLAG_NO_NAME_TRANSLATION) == 0) {
        if (dso->merger != NULL)
            result = dso->merger(dso, filespec1, filespec2);
        else if (dso->meth->dso_merger != NULL)
            result = dso->meth->dso_merger(dso, filespec1, filespec2);
    }
    return result;
}