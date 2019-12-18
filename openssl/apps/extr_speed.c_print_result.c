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
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  exit (int) ; 
 double* lengths ; 
 scalar_t__ mr ; 
 int /*<<< orphan*/ * names ; 
 double** results ; 

__attribute__((used)) static void print_result(int alg, int run_no, int count, double time_used)
{
    if (count == -1) {
        BIO_puts(bio_err, "EVP error!\n");
        exit(1);
    }
    BIO_printf(bio_err,
               mr ? "+R:%d:%s:%f\n"
               : "%d %s's in %.2fs\n", count, names[alg], time_used);
    results[alg][run_no] = ((double)count) / time_used * lengths[run_no];
}