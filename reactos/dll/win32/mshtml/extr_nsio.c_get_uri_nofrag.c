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
typedef  int /*<<< orphan*/  IUriBuilder ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateIUriBuilder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUriBuilder_CreateUriSimple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IUriBuilder_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUriBuilder_RemoveProperties (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUri_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUri_HasProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Uri_HAS_FRAGMENT ; 
 int /*<<< orphan*/  Uri_PROPERTY_FRAGMENT ; 

IUri *get_uri_nofrag(IUri *uri)
{
    IUriBuilder *uri_builder;
    IUri *ret;
    BOOL b;
    HRESULT hres;

    hres = IUri_HasProperty(uri, Uri_PROPERTY_FRAGMENT, &b);
    if(SUCCEEDED(hres) && !b) {
        IUri_AddRef(uri);
        return uri;
    }

    hres = CreateIUriBuilder(uri, 0, 0, &uri_builder);
    if(FAILED(hres))
        return NULL;

    hres = IUriBuilder_RemoveProperties(uri_builder, Uri_HAS_FRAGMENT);
    if(SUCCEEDED(hres))
        hres = IUriBuilder_CreateUriSimple(uri_builder, 0, 0, &ret);
    IUriBuilder_Release(uri_builder);
    if(FAILED(hres))
        return NULL;

    return ret;
}