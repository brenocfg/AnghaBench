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
typedef  int /*<<< orphan*/  OSSL_NAMEMAP ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_EVP ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_raise_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  EVP_R_BAD_ALGORITHM_NAME ; 
 int /*<<< orphan*/  EVP_R_CONFLICTING_ALGORITHM_NAME ; 
 char const NAME_SEPARATOR ; 
 int ossl_namemap_add_n (int /*<<< orphan*/ *,int,char const*,size_t) ; 
 int ossl_namemap_name2num_n (int /*<<< orphan*/ *,char const*,size_t) ; 
 char* strchr (char const*,char const) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int add_names_to_namemap(OSSL_NAMEMAP *namemap,
                                const char *names)
{
    const char *p, *q;
    size_t l;
    int id = 0;

    /* Check that we have a namemap and that there is at least one name */
    if (namemap == NULL) {
        ERR_raise(ERR_LIB_EVP, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }

    /*
     * Check that no name is an empty string, and that all names have at
     * most one numeric identity together.
     */
    for (p = names; *p != '\0'; p = (q == NULL ? p + l : q + 1)) {
        int this_id;

        if ((q = strchr(p, NAME_SEPARATOR)) == NULL)
            l = strlen(p);       /* offset to \0 */
        else
            l = q - p;           /* offset to the next separator */

        this_id = ossl_namemap_name2num_n(namemap, p, l);

        if (*p == '\0' || *p == NAME_SEPARATOR) {
            ERR_raise(ERR_LIB_EVP, EVP_R_BAD_ALGORITHM_NAME);
            return 0;
        }
        if (id == 0)
            id = this_id;
        else if (this_id != 0 && this_id != id) {
            ERR_raise_data(ERR_LIB_EVP, EVP_R_CONFLICTING_ALGORITHM_NAME,
                           "\"%.*s\" has an existing different identity %d (from \"%s\")",
                           l, p, this_id, names);
            return 0;
        }
    }

    /* Now that we have checked, register all names */
    for (p = names; *p != '\0'; p = (q == NULL ? p + l : q + 1)) {
        int this_id;

        if ((q = strchr(p, NAME_SEPARATOR)) == NULL)
            l = strlen(p);       /* offset to \0 */
        else
            l = q - p;           /* offset to the next separator */

        this_id = ossl_namemap_add_n(namemap, id, p, l);
        if (id == 0)
            id = this_id;
        else if (this_id != id) {
            ERR_raise_data(ERR_LIB_EVP, ERR_R_INTERNAL_ERROR,
                           "Got id %d when expecting %d", this_id, id);
            return 0;
        }
    }

    return id;
}