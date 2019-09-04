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
struct nvenc_data {int dummy; } ;
typedef  scalar_t__ HMODULE ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ GetModuleHandleA (char const*) ; 
 scalar_t__ LoadLibraryA (char const*) ; 
 int /*<<< orphan*/  error (char*,char const*) ; 

__attribute__((used)) static HANDLE get_lib(struct nvenc_data *enc, const char *lib)
{
	HMODULE mod = GetModuleHandleA(lib);
	if (mod)
		return mod;

	mod = LoadLibraryA(lib);
	if (!mod)
		error("Failed to load %s", lib);
	return mod;
}