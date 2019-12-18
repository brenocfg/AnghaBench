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
struct btf_type {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int BTF_INFO_KIND (int /*<<< orphan*/ ) ; 
#define  BTF_KIND_DATASEC 132 
#define  BTF_KIND_ENUM 131 
#define  BTF_KIND_INT 130 
#define  BTF_KIND_STRUCT 129 
#define  BTF_KIND_UNION 128 

__attribute__((used)) static bool btf_type_has_size(const struct btf_type *t)
{
	switch (BTF_INFO_KIND(t->info)) {
	case BTF_KIND_INT:
	case BTF_KIND_STRUCT:
	case BTF_KIND_UNION:
	case BTF_KIND_ENUM:
	case BTF_KIND_DATASEC:
		return true;
	}

	return false;
}