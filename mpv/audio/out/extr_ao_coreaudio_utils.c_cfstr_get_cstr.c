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
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  scalar_t__ CFIndex ;

/* Variables and functions */
 int /*<<< orphan*/  CA_CFSTR_ENCODING ; 
 int /*<<< orphan*/  CFStringGetCString (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFStringGetLength (int /*<<< orphan*/ ) ; 
 scalar_t__ CFStringGetMaximumSizeForEncoding (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* talloc_zero_size (int /*<<< orphan*/ *,scalar_t__) ; 

char *cfstr_get_cstr(CFStringRef cfstr)
{
    CFIndex size =
        CFStringGetMaximumSizeForEncoding(
            CFStringGetLength(cfstr), CA_CFSTR_ENCODING) + 1;
    char *buffer = talloc_zero_size(NULL, size);
    CFStringGetCString(cfstr, buffer, size, CA_CFSTR_ENCODING);
    return buffer;
}