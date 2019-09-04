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
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  int /*<<< orphan*/  CFIndex ;

/* Variables and functions */
 int /*<<< orphan*/  CFStringGetCString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFStringGetLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFStringGetMaximumSizeForEncoding (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_reserve (struct dstr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCFStringEncodingUTF8 ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dstr_from_cfstring(struct dstr *str, CFStringRef ref)
{
	CFIndex length   = CFStringGetLength(ref);
	CFIndex max_size = CFStringGetMaximumSizeForEncoding(length,
			kCFStringEncodingUTF8);
	dstr_reserve(str, max_size);

	if (!CFStringGetCString(ref, str->array, max_size,
				kCFStringEncodingUTF8))
		return false;

	str->len = strlen(str->array);
	return true;
}