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
typedef  int /*<<< orphan*/  X509_CRL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int X509_CRL_print_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XN_FLAG_COMPAT ; 

int X509_CRL_print(BIO *out, X509_CRL *x)
{
  return X509_CRL_print_ex(out, x, XN_FLAG_COMPAT);
}