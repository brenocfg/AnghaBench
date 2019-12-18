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
struct TYPE_3__ {scalar_t__ unicode; char const* gryph_name; } ;
typedef  TYPE_1__ HPDF_UnicodeGryphPair ;
typedef  scalar_t__ HPDF_UNICODE ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 TYPE_1__* HPDF_UNICODE_GRYPH_NAME_MAP ; 

const char*
HPDF_UnicodeToGryphName  (HPDF_UNICODE  unicode)
{
    const HPDF_UnicodeGryphPair* map = HPDF_UNICODE_GRYPH_NAME_MAP;

    HPDF_PTRACE ((" HPDF_UnicodeToGryphName\n"));

    while (map->unicode <= unicode) {
        if (map->unicode == unicode)
            return map->gryph_name;
        map++;
    }

    return HPDF_UNICODE_GRYPH_NAME_MAP[0].gryph_name;
}