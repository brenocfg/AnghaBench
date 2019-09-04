#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_1__ X509_ALGOR ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_printf (int /*<<< orphan*/ *,char*,char*) ; 
 int NID_undef ; 
 char* OBJ_nid2ln (int) ; 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 

int TS_X509_ALGOR_print_bio(BIO *bio, const X509_ALGOR *alg)
{
    int i = OBJ_obj2nid(alg->algorithm);
    return BIO_printf(bio, "Hash Algorithm: %s\n",
                      (i == NID_undef) ? "UNKNOWN" : OBJ_nid2ln(i));
}