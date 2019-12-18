#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_4__ {int Protect; scalar_t__ Type; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RDebugMap ;
typedef  TYPE_1__ MEMORY_BASIC_INFORMATION ;

/* Variables and functions */
 scalar_t__ MEM_PRIVATE ; 
#define  PAGE_EXECUTE 134 
#define  PAGE_EXECUTE_READ 133 
#define  PAGE_EXECUTE_READWRITE 132 
#define  PAGE_EXECUTE_WRITECOPY 131 
#define  PAGE_READONLY 130 
#define  PAGE_READWRITE 129 
#define  PAGE_WRITECOPY 128 
 int R_PERM_R ; 
 int R_PERM_RW ; 
 int R_PERM_RWX ; 
 int R_PERM_RX ; 
 int R_PERM_W ; 
 int R_PERM_X ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_map_type (TYPE_1__*) ; 
 int /*<<< orphan*/ * r_debug_map_new (char*,scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* r_str_newf (char*,char*,char const*) ; 

__attribute__((used)) static RDebugMap *add_map(RList *list, const char *name, ut64 addr, ut64 len, MEMORY_BASIC_INFORMATION *mbi) {
	int perm;
	char *map_type = get_map_type (mbi);

	switch (mbi->Protect) {
	case PAGE_EXECUTE:
		perm = R_PERM_X;
		break;
	case PAGE_EXECUTE_READ:
		perm = R_PERM_RX;
		break;
	case PAGE_EXECUTE_READWRITE:
		perm = R_PERM_RWX;
		break;
	case PAGE_READONLY:
		perm = R_PERM_R;
		break;
	case PAGE_READWRITE:
		perm = R_PERM_RW;
		break;
	case PAGE_WRITECOPY:
		perm = R_PERM_W;
		break;
	case PAGE_EXECUTE_WRITECOPY:
		perm = R_PERM_X;
		break;
	default:
		perm = 0;
	}
	char *map_name = r_str_newf ("%-8s %s", map_type, name);
	if (!map_name) {
		return NULL;
	}
	RDebugMap *mr = r_debug_map_new (map_name, addr, addr + len, perm, mbi->Type == MEM_PRIVATE);
	free (map_name);
	if (mr) {
		r_list_append (list, mr);
	}
	return mr;
}