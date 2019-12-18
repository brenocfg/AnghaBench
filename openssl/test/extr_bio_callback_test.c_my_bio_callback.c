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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 size_t MAXCOUNT ; 
 int* my_param_argi ; 
 long* my_param_argl ; 
 char const** my_param_argp ; 
 int /*<<< orphan*/ ** my_param_b ; 
 size_t my_param_count ; 
 int* my_param_oper ; 
 long* my_param_ret ; 

__attribute__((used)) static long my_bio_callback(BIO *b, int oper, const char *argp, int argi,
                            long argl, long ret)
{
    if (my_param_count >= MAXCOUNT)
        return -1;
    my_param_b[my_param_count]    = b;
    my_param_oper[my_param_count] = oper;
    my_param_argp[my_param_count] = argp;
    my_param_argi[my_param_count] = argi;
    my_param_argl[my_param_count] = argl;
    my_param_ret[my_param_count]  = ret;
    my_param_count++;
    return ret;
}