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
struct TYPE_3__ {scalar_t__ uri; scalar_t__ uri_builder; } ;
typedef  TYPE_1__ nsWineURI ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IUriBuilder_CreateUriSimple (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static BOOL ensure_uri(nsWineURI *This)
{
    HRESULT hres;

    assert(This->uri || This->uri_builder);

    if(!This->uri) {
        hres = IUriBuilder_CreateUriSimple(This->uri_builder, 0, 0, &This->uri);
        if(FAILED(hres)) {
            WARN("CreateUriSimple failed: %08x\n", hres);
            return FALSE;
        }
    }

    return TRUE;
}