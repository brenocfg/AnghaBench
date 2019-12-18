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
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 scalar_t__ bstr_startswith0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * utf_bom ; 
 char const** utf_enc ; 

__attribute__((used)) static const char *ms_bom_guess(bstr buf)
{
    for (int n = 0; n < 3; n++) {
        if (bstr_startswith0(buf, utf_bom[n]))
            return utf_enc[n];
    }
    return NULL;
}