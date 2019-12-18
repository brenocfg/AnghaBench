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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_EXCEPTION ; 
 scalar_t__ ERROR_NO_MORE_ITEMS ; 
 scalar_t__ ERROR_SUCCESS ; 
 int GUID_SIZE ; 
 scalar_t__ MsiEnumProductsW (int,int /*<<< orphan*/ *) ; 
 scalar_t__ MsiEnumRelatedProductsW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT get_products_count(const WCHAR *product, int *len)
{
    int i = 0;

    while (1)
    {
        WCHAR dataW[GUID_SIZE];
        UINT ret;

        /* all or related only */
        if (product)
            ret = MsiEnumRelatedProductsW(product, 0, i, dataW);
        else
            ret = MsiEnumProductsW(i, dataW);

        if (ret == ERROR_NO_MORE_ITEMS) break;

        if (ret != ERROR_SUCCESS)
            return DISP_E_EXCEPTION;

        i++;
    }

    *len = i;

    return S_OK;
}