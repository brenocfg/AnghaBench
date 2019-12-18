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
 int F_COND ; 
 int F_FPTYPE ; 
 int F_GPRSIZE_IN_Q ; 
 int F_LDS_SIZE ; 
 int F_LSE_SZ ; 
 int F_MISC ; 
 int F_N ; 
 int F_SF ; 
 int F_SIZEQ ; 
 int F_SSIZE ; 
 int F_T ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static inline bfd_boolean
opcode_has_special_coder (const aarch64_opcode *opcode)
{
  return (opcode->flags & (F_SF | F_LSE_SZ | F_SIZEQ | F_FPTYPE | F_SSIZE | F_T
	  | F_GPRSIZE_IN_Q | F_LDS_SIZE | F_MISC | F_N | F_COND)) ? TRUE
    : FALSE;
}