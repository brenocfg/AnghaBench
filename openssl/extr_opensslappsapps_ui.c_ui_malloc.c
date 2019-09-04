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
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,int,char const*) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 void* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  exit (int) ; 

__attribute__((used)) static void *ui_malloc(int sz, const char *what)
{
    void *vp = OPENSSL_malloc(sz);

    if (vp == NULL) {
        BIO_printf(bio_err, "Could not allocate %d bytes for %s\n", sz, what);
        ERR_print_errors(bio_err);
        exit(1);
    }
    return vp;
}