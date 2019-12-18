#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  nr_of_files; int /*<<< orphan*/  names; } ;
typedef  TYPE_1__ mf_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* talloc_strdup (TYPE_1__*,char const*) ; 

__attribute__((used)) static void mf_add(mf_t *mf, const char *fname)
{
    char *entry = talloc_strdup(mf, fname);
    MP_TARRAY_APPEND(mf, mf->names, mf->nr_of_files, entry);
}