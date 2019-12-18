#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__* HPDF_String ;
typedef  int HPDF_INT32 ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

HPDF_INT32
HPDF_String_Cmp  (HPDF_String s1,
                  HPDF_String s2)
{
    if (s1->len < s2->len) return -1;
    if (s1->len > s2->len) return +1;
    return memcmp(s1->value, s2->value, s1->len);
}