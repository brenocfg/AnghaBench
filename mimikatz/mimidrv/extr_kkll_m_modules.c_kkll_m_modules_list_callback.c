#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ImageBase; } ;
struct TYPE_5__ {scalar_t__ FileNameOffset; scalar_t__ FullPathName; int /*<<< orphan*/  ImageSize; TYPE_1__ BasicInfo; } ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PKIWI_BUFFER ;
typedef  TYPE_2__* PAUX_MODULE_EXTENDED_INFO ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

NTSTATUS kkll_m_modules_list_callback(SIZE_T szBufferIn, PVOID bufferIn, PKIWI_BUFFER outBuffer, PAUX_MODULE_EXTENDED_INFO pModule, PVOID pvArg, BOOLEAN * mustContinue)
{
	return kprintf(outBuffer, L"0x%p - %u\t%S\n", pModule->BasicInfo.ImageBase, pModule->ImageSize, pModule->FullPathName + pModule->FileNameOffset);
}