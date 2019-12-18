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
struct TYPE_6__ {TYPE_1__* mono; } ;
struct TYPE_5__ {int /*<<< orphan*/ * (* mono_runtime_invoke ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* mono_class_get_method_from_name ) (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * (* mono_class_from_name ) (int /*<<< orphan*/ *,char*,char*) ;int /*<<< orphan*/ * (* mono_assembly_get_image ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* mono_domain_assembly_open ) (int /*<<< orphan*/ *,char*) ;int /*<<< orphan*/  (* mono_thread_attach ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ RuntimeHost ;
typedef  int /*<<< orphan*/  MonoObject ;
typedef  int /*<<< orphan*/  MonoMethod ;
typedef  int /*<<< orphan*/  MonoImage ;
typedef  int /*<<< orphan*/  MonoDomain ;
typedef  int /*<<< orphan*/  MonoClass ;
typedef  int /*<<< orphan*/  MonoAssembly ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  IID__AppDomain ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RuntimeHost_GetIUnknownForObject (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub4 (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * stub5 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT RuntimeHost_GetIUnknownForDomain(RuntimeHost *This, MonoDomain *domain, IUnknown **punk)
{
    HRESULT hr;
    void *args[1];
    MonoAssembly *assembly;
    MonoImage *image;
    MonoClass *klass;
    MonoMethod *method;
    MonoObject *appdomain_object;
    IUnknown *unk;

    This->mono->mono_thread_attach(domain);

    assembly = This->mono->mono_domain_assembly_open(domain, "mscorlib");
    if (!assembly)
    {
        ERR("Cannot load mscorlib\n");
        return E_FAIL;
    }

    image = This->mono->mono_assembly_get_image(assembly);
    if (!image)
    {
        ERR("Couldn't get assembly image\n");
        return E_FAIL;
    }

    klass = This->mono->mono_class_from_name(image, "System", "AppDomain");
    if (!klass)
    {
        ERR("Couldn't get class from image\n");
        return E_FAIL;
    }

    method = This->mono->mono_class_get_method_from_name(klass, "get_CurrentDomain", 0);
    if (!method)
    {
        ERR("Couldn't get method from class\n");
        return E_FAIL;
    }

    args[0] = NULL;
    appdomain_object = This->mono->mono_runtime_invoke(method, NULL, args, NULL);
    if (!appdomain_object)
    {
        ERR("Couldn't get result pointer\n");
        return E_FAIL;
    }

    hr = RuntimeHost_GetIUnknownForObject(This, appdomain_object, &unk);

    if (SUCCEEDED(hr))
    {
        hr = IUnknown_QueryInterface(unk, &IID__AppDomain, (void**)punk);

        IUnknown_Release(unk);
    }

    return hr;
}