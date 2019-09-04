#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_2__ X509_NAME ;
struct TYPE_6__ {int /*<<< orphan*/  relativename; int /*<<< orphan*/  fullname; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_1__ name; } ;
typedef  TYPE_3__ DIST_POINT_NAME ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,int,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  X509_NAME_print_ex (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XN_FLAG_ONELINE ; 
 int /*<<< orphan*/  print_gens (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int print_distpoint(BIO *out, DIST_POINT_NAME *dpn, int indent)
{
    if (dpn->type == 0) {
        BIO_printf(out, "%*sFull Name:\n", indent, "");
        print_gens(out, dpn->name.fullname, indent);
    } else {
        X509_NAME ntmp;
        ntmp.entries = dpn->name.relativename;
        BIO_printf(out, "%*sRelative Name:\n%*s", indent, "", indent + 2, "");
        X509_NAME_print_ex(out, &ntmp, 0, XN_FLAG_ONELINE);
        BIO_puts(out, "\n");
    }
    return 1;
}