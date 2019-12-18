#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  parFmt ;
typedef  int /*<<< orphan*/  charFmt ;
typedef  char WCHAR ;
struct TYPE_6__ {int cbSize; scalar_t__ dwEffects; int /*<<< orphan*/  dwMask; } ;
struct TYPE_5__ {int cbSize; int dxStartIndent; int /*<<< orphan*/  dwMask; } ;
typedef  int /*<<< orphan*/  PCCERT_CONTEXT ;
typedef  TYPE_1__ PARAFORMAT2 ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_2__ CHARFORMATW ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_NAME_SIMPLE_DISPLAY_TYPE ; 
 scalar_t__ CFE_BOLD ; 
 int /*<<< orphan*/  CFM_BOLD ; 
 int /*<<< orphan*/  EM_SETCHARFORMAT ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_CERTIFICATE_NAMES ; 
 int MY_INDENT ; 
 int /*<<< orphan*/  PFM_STARTINDENT ; 
 int /*<<< orphan*/  SCF_SELECTION ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_cert_string_to_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_string_resource_with_paraformat_to_control (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  add_unformatted_text_to_control (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_cert_name_string(HWND hwnd, PCCERT_CONTEXT cert,
 DWORD nameFlags, int heading)
{
    WCHAR nl = '\n';
    HWND text = GetDlgItem(hwnd, IDC_CERTIFICATE_NAMES);
    CHARFORMATW charFmt;
    PARAFORMAT2 parFmt;

    memset(&charFmt, 0, sizeof(charFmt));
    charFmt.cbSize = sizeof(charFmt);
    charFmt.dwMask = CFM_BOLD;
    charFmt.dwEffects = CFE_BOLD;
    SendMessageW(text, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&charFmt);
    parFmt.cbSize = sizeof(parFmt);
    parFmt.dwMask = PFM_STARTINDENT;
    parFmt.dxStartIndent = MY_INDENT * 3;
    add_string_resource_with_paraformat_to_control(text, heading, &parFmt);
    charFmt.dwEffects = 0;
    SendMessageW(text, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&charFmt);
    add_cert_string_to_control(text, cert, CERT_NAME_SIMPLE_DISPLAY_TYPE,
     nameFlags);
    add_unformatted_text_to_control(text, &nl, 1);
    add_unformatted_text_to_control(text, &nl, 1);
    add_unformatted_text_to_control(text, &nl, 1);

}