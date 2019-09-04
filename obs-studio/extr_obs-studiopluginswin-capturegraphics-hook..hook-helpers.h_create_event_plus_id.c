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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  _snwprintf (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_event (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline HANDLE create_event_plus_id(const wchar_t *name, DWORD id)
{
	wchar_t new_name[64];
	_snwprintf(new_name, 64, L"%s%lu", name, id);
	return create_event(new_name);
}