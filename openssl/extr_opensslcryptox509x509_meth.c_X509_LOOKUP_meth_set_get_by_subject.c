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
typedef  int /*<<< orphan*/  X509_LOOKUP_get_by_subject_fn ;
struct TYPE_3__ {int /*<<< orphan*/  get_by_subject; } ;
typedef  TYPE_1__ X509_LOOKUP_METHOD ;

/* Variables and functions */

int X509_LOOKUP_meth_set_get_by_subject(X509_LOOKUP_METHOD *method,
    X509_LOOKUP_get_by_subject_fn get_by_subject)
{
    method->get_by_subject = get_by_subject;
    return 1;
}