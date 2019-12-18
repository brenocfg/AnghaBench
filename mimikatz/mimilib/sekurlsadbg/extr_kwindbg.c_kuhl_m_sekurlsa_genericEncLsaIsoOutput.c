#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  unkData2; int /*<<< orphan*/  unkData1; } ;
typedef  TYPE_1__* PENC_LSAISO_DATA_BLOB ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ENC_LSAISO_DATA_BLOB ; 
 int FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  kull_m_string_dprintf_hex (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

VOID kuhl_m_sekurlsa_genericEncLsaIsoOutput(PENC_LSAISO_DATA_BLOB blob, DWORD size)
{
	dprintf("\n\t   * unkData1 : "); kull_m_string_dprintf_hex(blob->unkData1, sizeof(blob->unkData1), 0);
	dprintf("\n\t     unkData2 : "); kull_m_string_dprintf_hex(blob->unkData2, sizeof(blob->unkData2), 0);
	dprintf("\n\t     Encrypted: "); kull_m_string_dprintf_hex(blob->data, size - FIELD_OFFSET(ENC_LSAISO_DATA_BLOB, data), 0);
}