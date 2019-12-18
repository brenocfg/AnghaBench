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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int inject_library_obf (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char*,int,char*,int,char*,int,char*,int,char*,int) ; 

__attribute__((used)) static inline int inject_library(HANDLE process, const wchar_t *dll)
{
	return inject_library_obf(process, dll, "E}mo|d[cefubWk~bgk",
				  0x7c3371986918e8f6, "Rqbr`T{cnor{Bnlgwz",
				  0x81bf81adc9456b35, "]`~wrl`KeghiCt",
				  0xadc6a7b9acd73c9b, "Zh}{}agHzfd@{",
				  0x57135138eb08ff1c, "DnafGhj}l~sX",
				  0x350bfacdf81b2018);
}