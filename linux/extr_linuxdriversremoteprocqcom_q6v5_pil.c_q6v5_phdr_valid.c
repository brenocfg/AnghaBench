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
struct elf32_phdr {scalar_t__ p_type; int p_flags; int /*<<< orphan*/  p_memsz; } ;

/* Variables and functions */
 scalar_t__ PT_LOAD ; 
 int QCOM_MDT_TYPE_HASH ; 
 int QCOM_MDT_TYPE_MASK ; 

__attribute__((used)) static bool q6v5_phdr_valid(const struct elf32_phdr *phdr)
{
	if (phdr->p_type != PT_LOAD)
		return false;

	if ((phdr->p_flags & QCOM_MDT_TYPE_MASK) == QCOM_MDT_TYPE_HASH)
		return false;

	if (!phdr->p_memsz)
		return false;

	return true;
}