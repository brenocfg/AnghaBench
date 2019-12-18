#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int WCHAR ;
typedef  size_t UINT ;
struct TYPE_4__ {int* bits; } ;
struct TYPE_5__ {int length; TYPE_1__ u; } ;
typedef  TYPE_2__ RECharSet ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
AddCharacterToCharSet(RECharSet *cs, WCHAR c)
{
    UINT byteIndex = (UINT)(c >> 3);
    assert(c <= cs->length);
    cs->u.bits[byteIndex] |= 1 << (c & 0x7);
}