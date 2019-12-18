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
typedef  enum aarch64_field_kind { ____Placeholder_aarch64_field_kind } aarch64_field_kind ;
typedef  int /*<<< orphan*/  aarch64_insn ;

/* Variables and functions */
 int /*<<< orphan*/  extract_field_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fields ; 

__attribute__((used)) static inline aarch64_insn
extract_field (enum aarch64_field_kind kind, aarch64_insn code,
	       aarch64_insn mask)
{
  return extract_field_2 (&fields[kind], code, mask);
}