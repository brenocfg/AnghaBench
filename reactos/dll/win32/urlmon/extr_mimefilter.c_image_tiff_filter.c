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
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int const*,int const*,int) ; 

__attribute__((used)) static BOOL image_tiff_filter(const BYTE *b, DWORD size)
{
    static const BYTE magic1[] = {0x4d,0x4d,0x00,0x2a};
    static const BYTE magic2[] = {0x49,0x49,0x2a,0xff};

    return size >= 4 && (!memcmp(b, magic1, 4) || !memcmp(b, magic2, 4));
}