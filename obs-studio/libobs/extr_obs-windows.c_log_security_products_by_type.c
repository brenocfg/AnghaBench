#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WSC_SECURITY_PRODUCT_STATE ;
struct TYPE_18__ {TYPE_2__* lpVtbl; } ;
struct TYPE_17__ {TYPE_1__* lpVtbl; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* Release ) (TYPE_4__*) ;int /*<<< orphan*/  (* get_Item ) (TYPE_4__*,int,TYPE_3__**) ;int /*<<< orphan*/  (* get_Count ) (TYPE_4__*,int*) ;int /*<<< orphan*/  (* Initialize ) (TYPE_4__*,int) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  (* Release ) (TYPE_3__*) ;int /*<<< orphan*/  (* get_ProductState ) (TYPE_3__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_ProductName ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;
typedef  int LONG ;
typedef  TYPE_3__ IWscProduct ;
typedef  TYPE_4__ IWSCProductList ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_str_for_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_str_for_type (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*,int,TYPE_3__**) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub8 (TYPE_4__*) ; 

__attribute__((used)) static void log_security_products_by_type(IWSCProductList *prod_list, int type)
{
	HRESULT hr;
	LONG count = 0;
	IWscProduct *prod;
	BSTR name;
	WSC_SECURITY_PRODUCT_STATE prod_state;

	hr = prod_list->lpVtbl->Initialize(prod_list, type);

	if (FAILED(hr))
		return;

	hr = prod_list->lpVtbl->get_Count(prod_list, &count);
	if (FAILED(hr)) {
		prod_list->lpVtbl->Release(prod_list);
		return;
	}

	for (int i = 0; i < count; i++) {
		hr = prod_list->lpVtbl->get_Item(prod_list, i, &prod);
		if (FAILED(hr))
			continue;

		hr = prod->lpVtbl->get_ProductName(prod, &name);
		if (FAILED(hr))
			continue;

		hr = prod->lpVtbl->get_ProductState(prod, &prod_state);
		if (FAILED(hr)) {
			SysFreeString(name);
			continue;
		}

		blog(LOG_INFO, "\t%S: %s (%s)", name,
		     get_str_for_state(prod_state), get_str_for_type(type));

		SysFreeString(name);
		prod->lpVtbl->Release(prod);
	}

	prod_list->lpVtbl->Release(prod_list);
}