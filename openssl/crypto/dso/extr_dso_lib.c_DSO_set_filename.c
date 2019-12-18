#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* filename; scalar_t__ loaded_filename; } ;
typedef  TYPE_1__ DSO ;

/* Variables and functions */
 int /*<<< orphan*/  DSO_F_DSO_SET_FILENAME ; 
 int /*<<< orphan*/  DSO_R_DSO_ALREADY_LOADED ; 
 int /*<<< orphan*/  DSOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strdup (char const*) ; 

int DSO_set_filename(DSO *dso, const char *filename)
{
    char *copied;

    if ((dso == NULL) || (filename == NULL)) {
        DSOerr(DSO_F_DSO_SET_FILENAME, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }
    if (dso->loaded_filename) {
        DSOerr(DSO_F_DSO_SET_FILENAME, DSO_R_DSO_ALREADY_LOADED);
        return 0;
    }
    /* We'll duplicate filename */
    copied = OPENSSL_strdup(filename);
    if (copied == NULL) {
        DSOerr(DSO_F_DSO_SET_FILENAME, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    OPENSSL_free(dso->filename);
    dso->filename = copied;
    return 1;
}