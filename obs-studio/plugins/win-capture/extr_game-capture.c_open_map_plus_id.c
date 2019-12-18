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
struct game_capture {int /*<<< orphan*/  app_sid; scalar_t__ is_app; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GC_MAPPING_FLAGS ; 
 int /*<<< orphan*/  OpenFileMappingW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _snwprintf (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_app_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline HANDLE open_map_plus_id(struct game_capture *gc,
				      const wchar_t *name, DWORD id)
{
	wchar_t new_name[64];
	_snwprintf(new_name, 64, L"%s%lu", name, id);

	debug("map id: %S", new_name);

	return gc->is_app ? open_app_map(gc->app_sid, new_name)
			  : OpenFileMappingW(GC_MAPPING_FLAGS, false, new_name);
}