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
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 int do_print_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  send_fp_chars ; 

int ASN1_STRING_print_ex_fp(FILE *fp, const ASN1_STRING *str, unsigned long flags)
{
    return do_print_ex(send_fp_chars, fp, flags, str);
}