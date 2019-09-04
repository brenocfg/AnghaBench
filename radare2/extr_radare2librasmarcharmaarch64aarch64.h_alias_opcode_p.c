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
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ aarch64_opcode ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int F_ALIAS ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static inline bfd_boolean
alias_opcode_p (const aarch64_opcode *opcode)
{
  return (opcode->flags & F_ALIAS) ? TRUE : FALSE;
}