#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ImageBase; } ;
struct TYPE_7__ {int /*<<< orphan*/  ImageSize; TYPE_1__ BasicInfo; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; scalar_t__ addr; } ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  scalar_t__ PVOID ;
typedef  scalar_t__ PUCHAR ;
typedef  TYPE_2__* PKKLL_M_MODULE_BASIC_INFOS ;
typedef  int /*<<< orphan*/  PKIWI_BUFFER ;
typedef  TYPE_3__* PAUX_MODULE_EXTENDED_INFO ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS kkll_m_modules_first_callback(SIZE_T szBufferIn, PVOID bufferIn, PKIWI_BUFFER outBuffer, PAUX_MODULE_EXTENDED_INFO pModule, PVOID pvArg, BOOLEAN * mustContinue)
{
	*mustContinue = FALSE;
	((PKKLL_M_MODULE_BASIC_INFOS) pvArg)->addr = (PUCHAR) pModule->BasicInfo.ImageBase;
	((PKKLL_M_MODULE_BASIC_INFOS) pvArg)->size = pModule->ImageSize;
	return STATUS_SUCCESS;
}