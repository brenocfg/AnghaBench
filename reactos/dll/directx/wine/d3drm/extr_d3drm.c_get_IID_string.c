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
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  IID_IDirect3DRMFrame ; 
 int /*<<< orphan*/  IID_IDirect3DRMFrame2 ; 
 int /*<<< orphan*/  IID_IDirect3DRMFrame3 ; 
 int /*<<< orphan*/  IID_IDirect3DRMMeshBuilder ; 
 int /*<<< orphan*/  IID_IDirect3DRMMeshBuilder2 ; 
 int /*<<< orphan*/  IID_IDirect3DRMMeshBuilder3 ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char* get_IID_string(const GUID* guid)
{
    if (IsEqualGUID(guid, &IID_IDirect3DRMFrame))
        return "IID_IDirect3DRMFrame";
    else if (IsEqualGUID(guid, &IID_IDirect3DRMFrame2))
        return "IID_IDirect3DRMFrame2";
    else if (IsEqualGUID(guid, &IID_IDirect3DRMFrame3))
        return "IID_IDirect3DRMFrame3";
    else if (IsEqualGUID(guid, &IID_IDirect3DRMMeshBuilder))
        return "IID_IDirect3DRMMeshBuilder";
    else if (IsEqualGUID(guid, &IID_IDirect3DRMMeshBuilder2))
        return "IID_IDirect3DRMMeshBuilder2";
    else if (IsEqualGUID(guid, &IID_IDirect3DRMMeshBuilder3))
        return "IID_IDirect3DRMMeshBuilder3";

    return "?";
}