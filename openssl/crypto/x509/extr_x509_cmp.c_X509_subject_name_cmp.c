#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  subject; } ;
struct TYPE_6__ {TYPE_1__ cert_info; } ;
typedef  TYPE_2__ X509 ;

/* Variables and functions */
 int X509_NAME_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int X509_subject_name_cmp(const X509 *a, const X509 *b)
{
    return X509_NAME_cmp(a->cert_info.subject, b->cert_info.subject);
}