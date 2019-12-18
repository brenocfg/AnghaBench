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
struct elfhdr {int /*<<< orphan*/  e_ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELFMAG ; 
 int /*<<< orphan*/  SELFMAG ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool elf_is_elf_file(const struct elfhdr *ehdr)
{
	return memcmp(ehdr->e_ident, ELFMAG, SELFMAG) == 0;
}