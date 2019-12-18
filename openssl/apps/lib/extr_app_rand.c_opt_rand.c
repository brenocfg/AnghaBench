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
typedef  enum r_range { ____Placeholder_r_range } r_range ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_strdup (int /*<<< orphan*/ ) ; 
#define  OPT_R_RAND 131 
#define  OPT_R_WRITERAND 130 
#define  OPT_R__FIRST 129 
#define  OPT_R__LAST 128 
 int loadfiles (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_arg () ; 
 int /*<<< orphan*/  save_rand_file ; 

int opt_rand(int opt)
{
    switch ((enum r_range)opt) {
    case OPT_R__FIRST:
    case OPT_R__LAST:
        break;
    case OPT_R_RAND:
        return loadfiles(opt_arg());
        break;
    case OPT_R_WRITERAND:
        OPENSSL_free(save_rand_file);
        save_rand_file = OPENSSL_strdup(opt_arg());
        break;
    }
    return 1;
}