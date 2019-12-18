#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {int /*<<< orphan*/  member_6; int /*<<< orphan*/ * member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_4__ {int member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; TYPE_1__ member_0; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_2__ KIWI_KEY_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SIGNATURE ; 
 int /*<<< orphan*/  CRYPT_EXPORTABLE ; 
 int /*<<< orphan*/  CRYPT_SILENT ; 
 int /*<<< orphan*/  MS_ENHANCED_PROV ; 
 int /*<<< orphan*/  PROV_RSA_FULL ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS kuhl_m_crypto_c_pkiwi(int argc, wchar_t * argv[])
{
	KIWI_KEY_INFO CaKi = {{NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_SILENT, 0, NULL, AT_SIGNATURE}, NULL, CRYPT_EXPORTABLE, 4096};


	return STATUS_SUCCESS;
}