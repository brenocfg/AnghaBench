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
typedef  int /*<<< orphan*/  PKULL_M_DPAPI_BLOB ;
typedef  int /*<<< orphan*/  LPCVOID ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  kull_m_dpapi_blob_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_dpapi_blob_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_dpapi_blob_descr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kull_m_dpapi_blob_quick_descr(DWORD level, LPCVOID data/*, DWORD size*/)
{
	PKULL_M_DPAPI_BLOB blob;
	if(blob = kull_m_dpapi_blob_create(data))
	{
		kull_m_dpapi_blob_descr(level, blob);
		kull_m_dpapi_blob_delete(blob);
	}
}