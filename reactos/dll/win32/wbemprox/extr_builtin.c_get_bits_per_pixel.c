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
typedef  int UINT32 ;
typedef  void* UINT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  BITSPIXEL ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 void* GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HORZRES ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERTRES ; 

__attribute__((used)) static UINT32 get_bits_per_pixel( UINT *hres, UINT *vres )
{
    HDC hdc = GetDC( NULL );
    UINT32 ret;

    if (!hdc) return 32;
    ret = GetDeviceCaps( hdc, BITSPIXEL );
    *hres = GetDeviceCaps( hdc, HORZRES );
    *vres = GetDeviceCaps( hdc, VERTRES );
    ReleaseDC( NULL, hdc );
    return ret;
}