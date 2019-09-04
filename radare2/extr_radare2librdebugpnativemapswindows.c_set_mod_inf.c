#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  pe_hdr ;
struct TYPE_16__ {int e_lfanew; } ;
struct TYPE_11__ {int Machine; int NumberOfSections; } ;
struct TYPE_15__ {TYPE_2__ FileHeader; } ;
struct TYPE_10__ {int NumberOfSections; } ;
struct TYPE_14__ {TYPE_1__ FileHeader; } ;
struct TYPE_13__ {scalar_t__ addr; } ;
struct TYPE_12__ {int sect_count; int /*<<< orphan*/ * sect_hdr; } ;
typedef  scalar_t__ SIZE_T ;
typedef  TYPE_3__ RWinModInfo ;
typedef  TYPE_4__ RDebugMap ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPCVOID ;
typedef  int /*<<< orphan*/  IMAGE_SECTION_HEADER ;
typedef  TYPE_5__ IMAGE_NT_HEADERS32 ;
typedef  TYPE_6__ IMAGE_NT_HEADERS ;
typedef  TYPE_7__ IMAGE_DOS_HEADER ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReadProcessMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 scalar_t__ is_pe_hdr (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static int set_mod_inf(HANDLE h_proc, RDebugMap *map, RWinModInfo *mod) {
	IMAGE_DOS_HEADER *dos_hdr;
	IMAGE_NT_HEADERS *nt_hdrs;
	IMAGE_NT_HEADERS32 *nt_hdrs32;
	IMAGE_SECTION_HEADER *sect_hdr;
	ut8 pe_hdr[0x1000];
	SIZE_T len;
	int mod_inf_fill;

	len = 0;
	sect_hdr = NULL;
	mod_inf_fill = -1;
	ReadProcessMemory (h_proc, (LPCVOID)(size_t)map->addr, (LPVOID)pe_hdr, sizeof (pe_hdr), &len);
	if (len == (SIZE_T)sizeof (pe_hdr) && is_pe_hdr (pe_hdr)) {
		dos_hdr = (IMAGE_DOS_HEADER *)pe_hdr;
		if (!dos_hdr) {
			goto err_set_mod_info;
		}
		nt_hdrs = (IMAGE_NT_HEADERS *)((char *)dos_hdr + dos_hdr->e_lfanew);
		if (!nt_hdrs) {
			goto err_set_mod_info;
		}
		if (nt_hdrs->FileHeader.Machine == 0x014c) { // check for x32 pefile
			nt_hdrs32 = (IMAGE_NT_HEADERS32 *)((char *)dos_hdr + dos_hdr->e_lfanew);
			mod->sect_count = nt_hdrs32->FileHeader.NumberOfSections;
			sect_hdr = (IMAGE_SECTION_HEADER *)((char *)nt_hdrs32 + sizeof (IMAGE_NT_HEADERS32));
		} else {
			mod->sect_count = nt_hdrs->FileHeader.NumberOfSections;
			sect_hdr = (IMAGE_SECTION_HEADER *)((char *)nt_hdrs + sizeof (IMAGE_NT_HEADERS));
		}
		mod->sect_hdr = (IMAGE_SECTION_HEADER *)malloc (sizeof (IMAGE_SECTION_HEADER) * mod->sect_count);
		if (!mod->sect_hdr) {
			perror ("malloc set_mod_inf()");
			goto err_set_mod_info;
		}
		memcpy (mod->sect_hdr, sect_hdr, sizeof (IMAGE_SECTION_HEADER) * mod->sect_count);
		mod_inf_fill = 0;
	}
err_set_mod_info:
	if (mod_inf_fill == -1) {
		R_FREE (mod->sect_hdr);
	}
	return mod_inf_fill;
}