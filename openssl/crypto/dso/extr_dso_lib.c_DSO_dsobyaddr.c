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
typedef  int /*<<< orphan*/  DSO ;

/* Variables and functions */
 int /*<<< orphan*/ * DSO_load (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int DSO_pathbyaddr (void*,char*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_malloc (int) ; 

DSO *DSO_dsobyaddr(void *addr, int flags)
{
    DSO *ret = NULL;
    char *filename = NULL;
    int len = DSO_pathbyaddr(addr, NULL, 0);

    if (len < 0)
        return NULL;

    filename = OPENSSL_malloc(len);
    if (filename != NULL
            && DSO_pathbyaddr(addr, filename, len) == len)
        ret = DSO_load(NULL, filename, NULL, flags);

    OPENSSL_free(filename);
    return ret;
}