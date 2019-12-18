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
typedef  int /*<<< orphan*/  WICPixelFormatGUID ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GUID_WICPixelFormat1bppIndexed ; 
 int /*<<< orphan*/  GUID_WICPixelFormatBlackWhite ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL is_1bpp_format(const WICPixelFormatGUID *format)
{
    return IsEqualGUID(format, &GUID_WICPixelFormatBlackWhite) ||
           IsEqualGUID(format, &GUID_WICPixelFormat1bppIndexed);
}