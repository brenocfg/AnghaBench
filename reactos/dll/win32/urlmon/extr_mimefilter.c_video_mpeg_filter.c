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

__attribute__((used)) static BOOL video_mpeg_filter(const BYTE *b, DWORD size)
{
    return size > 4
        && !b[0] && !b[1] && b[2] == 0x01
        && (b[3] == 0xb3 || b[3] == 0xba);
}