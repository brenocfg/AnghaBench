#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  parFmt ;
typedef  int /*<<< orphan*/  charFmt ;
typedef  char WCHAR ;
struct TYPE_11__ {int cbSize; void* dwEffects; int /*<<< orphan*/  dwMask; } ;
struct TYPE_10__ {int cbSize; int dxStartIndent; int /*<<< orphan*/  dwMask; } ;
struct TYPE_9__ {TYPE_1__* pCertInfo; } ;
struct TYPE_8__ {int /*<<< orphan*/  NotAfter; int /*<<< orphan*/  NotBefore; } ;
typedef  TYPE_2__* PCCERT_CONTEXT ;
typedef  TYPE_3__ PARAFORMAT2 ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_4__ CHARFORMATW ;

/* Variables and functions */
 void* CFE_BOLD ; 
 int /*<<< orphan*/  CFM_BOLD ; 
 int /*<<< orphan*/  EM_SETCHARFORMAT ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_CERTIFICATE_NAMES ; 
 int /*<<< orphan*/  IDS_VALID_FROM ; 
 int /*<<< orphan*/  IDS_VALID_TO ; 
 int MY_INDENT ; 
 int /*<<< orphan*/  PFM_STARTINDENT ; 
 int /*<<< orphan*/  SCF_SELECTION ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_date_string_to_control (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_string_resource_to_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_string_resource_with_paraformat_to_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  add_unformatted_text_to_control (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_cert_validity_period(HWND hwnd, PCCERT_CONTEXT cert)
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
    add_string_resource_with_paraformat_to_control(text, IDS_VALID_FROM,
     &parFmt);
    charFmt.dwEffects = 0;
    SendMessageW(text, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&charFmt);
    add_date_string_to_control(text, &cert->pCertInfo->NotBefore);
    charFmt.dwEffects = CFE_BOLD;
    SendMessageW(text, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&charFmt);
    add_string_resource_to_control(text, IDS_VALID_TO);
    charFmt.dwEffects = 0;
    SendMessageW(text, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&charFmt);
    add_date_string_to_control(text, &cert->pCertInfo->NotAfter);
    add_unformatted_text_to_control(text, &nl, 1);
}