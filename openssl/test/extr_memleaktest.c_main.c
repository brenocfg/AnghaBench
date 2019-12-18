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

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_MEM_CHECK_ON ; 
 int /*<<< orphan*/  CRYPTO_mem_ctrl (int /*<<< orphan*/ ) ; 
 int CRYPTO_mem_leaks_fp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_set_mem_debug (int) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_malloc (int) ; 
 scalar_t__ TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_int_ne (int,int) ; 
 int /*<<< orphan*/  TEST_ptr (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 

int main(int argc, char *argv[])
{
#ifndef OPENSSL_NO_CRYPTO_MDEBUG
    char *p;
    char *lost;
    int noleak;

    p = getenv("OPENSSL_DEBUG_MEMORY");
    if (p != NULL && strcmp(p, "on") == 0)
        CRYPTO_set_mem_debug(1);
    CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);

    lost = OPENSSL_malloc(3);
    if (!TEST_ptr(lost))
        return EXIT_FAILURE;

    if (argv[1] && strcmp(argv[1], "freeit") == 0) {
        OPENSSL_free(lost);
        lost = NULL;
    }

    noleak = CRYPTO_mem_leaks_fp(stderr);
    /* If -1 return value something bad happened */
    if (!TEST_int_ne(noleak, -1))
        return EXIT_FAILURE;

    return TEST_int_eq(lost != NULL, noleak == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
#else
    return EXIT_SUCCESS;
#endif
}