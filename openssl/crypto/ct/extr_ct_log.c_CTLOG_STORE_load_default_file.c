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
typedef  int /*<<< orphan*/  CTLOG_STORE ;

/* Variables and functions */
 char* CTLOG_FILE ; 
 int /*<<< orphan*/  CTLOG_FILE_EVP ; 
 int CTLOG_STORE_load_file (int /*<<< orphan*/ *,char const*) ; 
 char* ossl_safe_getenv (int /*<<< orphan*/ ) ; 

int CTLOG_STORE_load_default_file(CTLOG_STORE *store)
{
    const char *fpath = ossl_safe_getenv(CTLOG_FILE_EVP);

    if (fpath == NULL)
      fpath = CTLOG_FILE;

    return CTLOG_STORE_load_file(store, fpath);
}