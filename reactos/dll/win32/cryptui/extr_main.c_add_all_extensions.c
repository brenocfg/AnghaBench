#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct detail_data {TYPE_1__* pCertViewInfo; } ;
struct TYPE_6__ {TYPE_2__* pCertInfo; } ;
struct TYPE_5__ {size_t cExtension; int /*<<< orphan*/ * rgExtension; } ;
struct TYPE_4__ {TYPE_3__* pCertContext; } ;
typedef  TYPE_3__* PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  add_cert_extension_detail (int /*<<< orphan*/ ,struct detail_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_all_extensions(HWND hwnd, struct detail_data *data)
{
    DWORD i;
    PCCERT_CONTEXT cert = data->pCertViewInfo->pCertContext;

    for (i = 0; i < cert->pCertInfo->cExtension; i++)
        add_cert_extension_detail(hwnd, data, &cert->pCertInfo->rgExtension[i]);
}