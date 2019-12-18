#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_EXTENSION ;
struct TYPE_4__ {int /*<<< orphan*/  requestExtensions; } ;
struct TYPE_5__ {TYPE_1__ tbsRequest; } ;
typedef  TYPE_2__ OCSP_REQUEST ;

/* Variables and functions */
 int /*<<< orphan*/ * X509v3_add_ext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int OCSP_REQUEST_add_ext(OCSP_REQUEST *x, X509_EXTENSION *ex, int loc)
{
    return (X509v3_add_ext(&(x->tbsRequest.requestExtensions), ex, loc) !=
            NULL);
}