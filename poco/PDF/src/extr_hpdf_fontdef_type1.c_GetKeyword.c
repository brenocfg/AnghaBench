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
typedef  scalar_t__ HPDF_UINT ;

/* Variables and functions */
 scalar_t__ HPDF_IS_WHITE_SPACE (char const) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ HPDF_StrLen (char const*,int) ; 

__attribute__((used)) static const char*
GetKeyword  (const char  *src,
             char        *keyword,
             HPDF_UINT        len)
{
    HPDF_UINT src_len = HPDF_StrLen (src, -1);

    HPDF_PTRACE ((" GetKeyword\n"));

    if (!keyword || src_len == 0 || len == 0)
        return NULL;

    *keyword = 0;

    while (len > 1) {
        if (HPDF_IS_WHITE_SPACE(*src)) {
            *keyword = 0;

            while (HPDF_IS_WHITE_SPACE(*src))
                src++;
            return src;
        }

        *keyword++ = *src++;
        len--;
    }

    *keyword = 0;
    return NULL;
}