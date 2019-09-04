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
struct TYPE_3__ {int /*<<< orphan*/ * tst_info; int /*<<< orphan*/  status_info; } ;
typedef  TYPE_1__ TS_RESP ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  TS_STATUS_INFO_print_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_TST_INFO_print_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int TS_RESP_print_bio(BIO *bio, TS_RESP *a)
{
    BIO_printf(bio, "Status info:\n");
    TS_STATUS_INFO_print_bio(bio, a->status_info);

    BIO_printf(bio, "\nTST info:\n");
    if (a->tst_info != NULL)
        TS_TST_INFO_print_bio(bio, a->tst_info);
    else
        BIO_printf(bio, "Not included.\n");

    return 1;
}