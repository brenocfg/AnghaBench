#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mp_format; int /*<<< orphan*/  const* subtype; } ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  const KSDATAFORMAT_SPECIFIER_NONE ; 
 TYPE_1__* wasapi_formats ; 

__attribute__((used)) static const GUID *format_to_subtype(int format)
{
    for (int i = 0; wasapi_formats[i].mp_format; i++) {
        if (format == wasapi_formats[i].mp_format)
            return wasapi_formats[i].subtype;
    }
    return &KSDATAFORMAT_SPECIFIER_NONE;
}