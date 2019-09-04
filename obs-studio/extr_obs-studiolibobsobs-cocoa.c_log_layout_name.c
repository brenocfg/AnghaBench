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
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  TISInputSourceRef ;
typedef  int /*<<< orphan*/  CFStringRef ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  TISGetInputSourceProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_from_cfstring (struct dstr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kTISPropertyInputSourceID ; 

__attribute__((used)) static bool log_layout_name(TISInputSourceRef tis)
{
	struct dstr layout_name = {0};
	CFStringRef sid = (CFStringRef)TISGetInputSourceProperty(tis,
					kTISPropertyInputSourceID);
	if (!sid) {
		blog(LOG_ERROR, "hotkeys-cocoa: Failed getting InputSourceID");
		return false;
	}

	if (!dstr_from_cfstring(&layout_name, sid)) {
		blog(LOG_ERROR, "hotkeys-cocoa: Could not convert InputSourceID"
				" to CString");
		goto fail;
	}

	blog(LOG_INFO, "hotkeys-cocoa: Using layout '%s'", layout_name.array);

	dstr_free(&layout_name);
	return true;

fail:
	dstr_free(&layout_name);
	return false;
}