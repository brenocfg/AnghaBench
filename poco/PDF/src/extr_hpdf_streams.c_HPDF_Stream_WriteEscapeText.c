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
typedef  int /*<<< orphan*/  HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_Stream ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_LIMIT_MAX_STRING_LEN ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_StrLen (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Stream_WriteEscapeText2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

HPDF_STATUS
HPDF_Stream_WriteEscapeText  (HPDF_Stream    stream,
                              const char    *text)
{
    HPDF_UINT len;

    HPDF_PTRACE((" HPDF_Stream_WriteEscapeText\n"));

    len = (text == NULL) ? 0 : HPDF_StrLen (text, HPDF_LIMIT_MAX_STRING_LEN);

    return HPDF_Stream_WriteEscapeText2(stream, text, len);
}