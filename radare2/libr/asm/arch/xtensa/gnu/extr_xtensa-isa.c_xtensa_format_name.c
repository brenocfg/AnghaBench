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
struct TYPE_5__ {TYPE_1__* formats; } ;
typedef  TYPE_2__ xtensa_isa_internal ;
typedef  scalar_t__ xtensa_isa ;
typedef  size_t xtensa_format ;
struct TYPE_4__ {char const* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FORMAT (TYPE_2__*,size_t,int /*<<< orphan*/ *) ; 

const char *
xtensa_format_name (xtensa_isa isa, xtensa_format fmt)
{
  xtensa_isa_internal *intisa = (xtensa_isa_internal *) isa;
  CHECK_FORMAT (intisa, fmt, NULL);
  return intisa->formats[fmt].name;
}