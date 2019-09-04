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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut32 ;
struct TYPE_3__ {int shstrtab_size; scalar_t__ shstrtab; } ;
typedef  TYPE_1__ ELFOBJ ;

/* Variables and functions */
 int /*<<< orphan*/ * r_mem_mem (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static inline int needle(ELFOBJ *bin, const char *s) {
	if (bin->shstrtab) {
		ut32 len = bin->shstrtab_size;
		if (len > 4096) {
			len = 4096; // avoid slow loading .. can be buggy?
		}
		return r_mem_mem ((const ut8*)bin->shstrtab, len,
				(const ut8*)s, strlen (s)) != NULL;
	}
	return 0;
}