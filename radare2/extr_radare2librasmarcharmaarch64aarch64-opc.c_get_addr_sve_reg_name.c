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
typedef  scalar_t__ aarch64_opnd_qualifier_t ;

/* Variables and functions */
 scalar_t__ AARCH64_OPND_QLF_S_D ; 
 scalar_t__ AARCH64_OPND_QLF_S_S ; 
 int /*<<< orphan*/  assert (int) ; 
 char const*** sve_reg ; 

__attribute__((used)) static inline const char *
get_addr_sve_reg_name (int regno, aarch64_opnd_qualifier_t qualifier)
{
  assert (qualifier == AARCH64_OPND_QLF_S_S
	  || qualifier == AARCH64_OPND_QLF_S_D);
  return sve_reg[qualifier == AARCH64_OPND_QLF_S_D][regno];
}