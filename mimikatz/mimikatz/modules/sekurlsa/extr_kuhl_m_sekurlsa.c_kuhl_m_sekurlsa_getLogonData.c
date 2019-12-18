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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  const* member_0; } ;
typedef  int /*<<< orphan*/  PKUHL_M_SEKURLSA_PACKAGE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_1__ KUHL_M_SEKURLSA_GET_LOGON_DATA_CALLBACK_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  kuhl_m_sekurlsa_enum (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kuhl_m_sekurlsa_enum_callback_logondata ; 

NTSTATUS kuhl_m_sekurlsa_getLogonData(const PKUHL_M_SEKURLSA_PACKAGE * lsassPackages, ULONG nbPackages)
{
	KUHL_M_SEKURLSA_GET_LOGON_DATA_CALLBACK_DATA OptionalData = {lsassPackages, nbPackages};
	return kuhl_m_sekurlsa_enum(kuhl_m_sekurlsa_enum_callback_logondata, &OptionalData);
}